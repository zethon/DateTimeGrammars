# bbcpp

## Introduction

bbcpp is a C++ library for parsing BBCode, or Bulletin Board Code, a markup language used to format posts in many message boards.

This library requires the Boost C++ libraries.

**NOTE**: Currently this project is being worked on in a seperate repo. Once it is past initial develoment, I will replace the `bbcpp` project's code with this.

## Supported BBCode Element Typs

### Simple Elements

1. `[B]This is bold text[/B]`

### Value Elements

1. `[COLOR="green"]`
    * with quotes
1. `[COLOR=green]`
    * without quotes

### `QUOTE` Element

1. `[QUOTE user=Username postid=1234]` 
    * a key-value pair of values. In theory they are space delimited unless quoted (used with phpBB)
1. `[QUOTE="username, post: 1799684, member: 11733"]`
    * another key-value pair format except the first argument is assumed to be the username (used with XenForo)   
1. `[QUOTE=Username;1234]` 
    * `Username` is the name of the user being quoted and `1234` is the postid (used with vBulletin)

## BNF

```
document = element | document element
element = quote-tag | simple-tag | content

tag = quote-tag

tag-open = tag-start tag-name tag-end
tag-start = "["
tag-end = "]"
tag-name = characters - whitespace 


whitespace = ? whitespace characters ?s
characters = ? unicode characters ?

 <document> ::= <element> | <document> <element>
 <element> ::= <tag> | <content>
 <tag> ::= <opening_tag_1> | <opening_tag> <content> <closing_tag>
 <opening_tag> ::= <opening_tag_1> | <opening_tag_2>
 <opening_tag_1> ::= <tag_prefix> <tag_end>
 <opening_tag_2> ::= <tag_prefix> '=' <attr> <tag_end>
 <tag_prefix> ::= <tag_start> <tag_name>
 <tag_start> ::= '['
 <tag_end> ::= ']'
 <attr> ::= <character> | <attr> <character>
 <closing_tag> ::= <tag_start> '/' <tag_name> <tag_end>
 <tag_name> ::= <character_non-key> | <tag_name> <character_non-key_2>
 <content> ::= <character> | <content> <character>
 <character> ::= unicode
 <character_non-key> ::= unicode not including '[', '=', ']', '/'
 <character_non-key_2> ::= <character_non-key> | '/'
```

