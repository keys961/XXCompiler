program MixedTest2;
type
	int = integer;
var
	outReal : real;
	result : int;
function max(num1: integer; num2 :integer) :integer;

function min(num1: integer; num2:integer):integer;
var
	r : int;
	begin
		outReal := 10.0;
		if (num1 < num2) then min := num1
		else min := num2;
	end;
begin
	result := min(2,1);
end;
begin
	max(1,2);
	write(outReal);
	write(result);
end.