// Just used for type checking...
// It will cause an error when type checking!
program test11witherror;
const
	con = 10;
var
	i : integer;
	j : char;
	k : array[1..20] of char;
function ff(h : real) : char;
begin
end;
begin
	con := 100;
	i := ff(i,i);
	k[i] := k;
	i := j;
end.