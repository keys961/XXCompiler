program HelloWorld;
type
	int = integer;
var
	s:int;
	result:int;
begin
	s := 0;
	result := 0;
	while s < 100 do
	begin
		result := result + s;
		s := s + 1;
	end;
	write(result);
end.