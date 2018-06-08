program MixedTest2;
type
	int = integer;
var
	out : int;
	result : int;
function min(num1: integer; num2:integer):integer;
begin
	out := 10;
	if (num1 < num2) then result := num1 else result := num2;
end;
begin
	min(1,2);
	write(out);
	write(result);
end.