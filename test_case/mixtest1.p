program MixedTest1;
const
    sub = 'a';
type
	int = integer;
	book = record
		id1 : integer;
		id2 : integer;
		id3 : real;
		name : char
	end;
var
	b1 : book;
	b2 : book;
	re : integer;
	ar : array[1..10] of book;
	i : integer;
begin
	b1.id1 := 1;
	ar[1] := b1;
	re := 1;
	re := 2 * re;
	b1.name := 'a';
	write(b1.id1);
	write(re);
end.