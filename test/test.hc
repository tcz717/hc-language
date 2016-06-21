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