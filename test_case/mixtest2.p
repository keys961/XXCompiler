program MixedTest2;
type
	int = integer;
var
	out : int;
	result : int;
	jj : int;
	kk : int;
function min(num1: integer; num2:integer):integer;
begin
	out := 10;
	if (num1 < num2) then result := num1 else result := num2;
end;
begin
	min(1,2);
	write(out);
	write(result);
	kk := 10;
	for jj := 0 to 100 do
    begin
    	kk := jj + kk;
    end;
    write(kk);
end.