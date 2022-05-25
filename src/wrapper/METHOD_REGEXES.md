Replace ICore with the name of your interface

Remove all comments:
`\/\/.+\n`
empty

Remove all virtual keywords:
`(virtual|inline) `
empty

Remove all method qualifiers:
` ?(const)? ?(= 0)?;`
`;`

Replace all types having commas in the definition with aliases

Remove all implementations manually

Prepare void functions:
`void (\w+?)\((.*)\)`
`WRAP_BASIC_CALL(ICore, $1, PARAMETERS($2))`

Prepare not-void functions:
`^([\w,*<>& ]+?) (\w+?)\((.*)\)`
`WRAP_BASIC_CALL_RETURN(ICore, $2, RETURN_VALUE($1), PARAMETERS($3))`

Convert return values:
`RETURN_VALUE\(((?:const )?([\w,*<>& ]+?)(?:&|\*)?)\)`
`($1, TO_JS_FN($2))`

Convert parameters:
`(PARAMETERS\(.*?)((?:const )?([a-zA-Z0-9<>_]+)(?:&|\*)?) ([a-zA-Z0-9]+)(?: = (0\.f|[a-zA-Z0-9]+(?:\(.*?\))?))?(,|\))`
`($2, FROM_JS_FN($3), $4, $5), $1$6`

Remove PARAMETERS words
`, PARAMETERS\([ ,]*\)`
empty

Remove all trailing commas
`, \)`
`)`

Remove all ;
`(WRAP_BASIC_CALL.+);\n`
`$1\n`

