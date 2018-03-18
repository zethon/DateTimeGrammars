# Notes

## Restricting numerical values

This seems to be a way to restrict values even if they parse. For example, the `_daynum` below will only parse if the value is less than 31

    boost::spirit::qi::rule<Iterator, unsigned int()> _daynum;
    ...
    _daynum = bsq::uint_parser<int, 10, 1, 2>() >> bsq::eps(bsq::_val <= 31);

## Using a Constructor

Here we are able to create a `QDate` object using the following constructor: `QDate(int y, int m, int d)`

    struct DateParser : bsq::grammar<Iterator, QDate()>
    ...
        _date = _yearnum
            >> '-'
            >> _monthnum
            >> '-'
            >> _daynum;

        _query = _date[
            bsq::_val = bph::construct<QDate>(
                    bph::at_c<0>(bsq::_1), 
                    bph::at_c<1>(bsq::_1), 
                    bph::at_c<2>(bsq::_1)
                )
            ];
        ...

    boost::spirit::qi::rule<Iterator, UIntTriplet()> _date;
    boost::spirit::qi::rule<Iterator, QDate() > _query;

The `_yearnum` and other rules are just `uint_parser` rules putting restrictions on the integers for each value. 

The thing to note here is that `bsq::_1` referenced in the `_query` definition refers to the first value return from `_date`, which is in the `UIntTriplet` which is defined as: `using UIntTriplet = std::tuple<unsigned int, unsigned int, unsigned int>;`. We then use the Phoenix operator `at_c` to pick out the the individual values to pass to the `QDate` contructor via `bph::construct`.

## Adding Functions that Can be Called "In" a Rule

After constructing our `QDate` object, we want to make sure the date is valid. For example, our Spirit parser will allow `2018-02-31` to parse but that is obviously an invalid date. Luckily `QDate` has a method called `isValid()` that tells us exactly what we need to do.

#### Motivation
The reason we want to call this in grammar as opposed to post-processing is because we want our grammar to be smart enough to parse things like `07-18-2018`. It will first try to parse this as `DDMMYYYY` and then revert to `MMDDYYYY`. We want to avoid multiple calls to multiple parsers, so we want to check **in** the grammar if the date is valid.

#### Code
First define a functor that implements the function. In this case it's pretty simple:

    struct QDate_isValid_impl
    {
        typedef bool result_type;

        bool operator()(const QDate& date) const
        {
            return date.isValid();
        }
    };

Secondly, within our grammar we declare a static member object using Boost's Phoenix to bind it to our implementation:

    template<typename Iterator>
    struct DateParser : bsq::grammar<Iterator, QDate()>
    {
        ...
        static const boost::phoenix::function<QDate_isValid_impl> is_valid;
        ...
    };

And lastly, we define the member in the outer namepace, per the requirements of C++.

    template <typename Iterator>
    const boost::phoenix::function<QDate_isValid_impl> DateParser<Iterator>::is_valid;

With this, we can now use function as follows:

    _query = _dateYMD[
        bsq::_val = bph::construct<QDate>(
                bph::at_c<0>(bsq::_1), 
                bph::at_c<1>(bsq::_1), 
                bph::at_c<2>(bsq::_1)
            ),
        bph::if_(!is_valid(bsq::_val))
            [
                bsq::_pass = false
            ]
        ];

This rule will construct a `QDate` object and then pass that object to our function. If the rule is invalid, we set `bsq::_pass = false` which will cause the parser to fail.