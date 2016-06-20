## hc Language
---
This is a c-style language used for `Human Resource Machine`. 

And this project is a compiler for hc.

Example:
```
//hc
#heap(15)
pre #14=0;
var size=0;
var data@1[8];
loop:main
{
	var in@0=inbox();
	for(i=size;i!=0;i--)
	{
		if(in==[i])
		{
			coninue:main;
		}
	}
	outbox(in);
	size++;
}
```
It will be converted to `Human Resource Machine`'s Language like following:
```
-- HUMAN RESOURCE MACHINE PROGRAM --

    COPYFROM 14
    COPYTO   12
a:
b:
    COPYFROM 14
    COPYTO   13
    INBOX   
    COPYTO   11
    COPYFROM 13
c:
    SUB      12
    JUMPZ    d
    COPYFROM 11
    SUB      [13]
    JUMPZ    b
    BUMPUP   13
    JUMP     c
d:
    COPYFROM 11
    COPYTO   [13]
    OUTBOX  
    BUMPUP   12
    JUMP     a

```