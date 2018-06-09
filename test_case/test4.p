program test4;
type
	int = integer;
var
	result:int;

procedure min(num1:integer; num2:integer;r:integer);
begin
	if (num1 < num2) then r := num1 else r:= num2;
end;

begin
	min(1,2);
	write(result);
end.