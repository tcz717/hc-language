## hc Language
---
This is a c-style language used for `Human Resource Machine`. 

And this project is a compiler for hc.

Example:
```
//hc
#heap(15)
pre #14=0;
var size@14;
var data@1[8];
loop:main
{
	var in@0=inbox();
	for(var i=size;i!=0;i--)
	{
		if(in==[i])
		{
			coninue:main;
		}
	}
	size++;
    [size]=in;
	outbox(in);
}
```
It will be converted to `Human Resource Machine`'s Language like following:
```
-- HUMAN RESOURCE MACHINE PROGRAM --

    JUMP     b
a:
    BUMPUP   14
    COPYFROM 0
    COPYTO   [14]
    OUTBOX  
b:
c:
    INBOX   
    COPYTO   0
    COPYFROM 14
    COPYTO   13
d:
    JUMPZ    a
    COPYFROM 0
    SUB      [13]
    JUMPZ    c
    BUMPDN   13
    JUMP     d

```