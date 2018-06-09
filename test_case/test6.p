program test6;
type
	int = integer;
var
	s : int;
	result:int;
begin
	s := 0;
	result := 0;
	for s := 0 to 100 do
	begin
		result := result + s;
	end;
	write(result);
end.