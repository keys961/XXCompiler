// Test with nearly all functions..
program test9;
const
	ccc = 1;
	sub = 'a';
type
	int = integer;
	book = record
		id : integer;
		name : char
	end;
var
	n1 : int;
	n2 : int;
	n3 : int;
	b : book;
	ar : array[1..20] of string;
	s:int;
    re:int;
procedure max(num1:integer; num2 :integer; n :integer);
var
	result:int;
begin
    if (num1 < num2) then result := num2 else result := num1;
	n := 1;
end;
begin
	n1 := -1;
	n2 := -n1+n2;
	max(n1,n2,n3);
	b.id := n1;
	ar[0] := 'b';
    s := 0;
	re := 0;
	while s < 100 do
	begin
		re := re + s;
		s := s + 1;
	end;
	write(re);
end.