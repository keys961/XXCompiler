program test12;
type
	int = integer;
var
	s : int;
	result : int;
begin
	s := 0;
	result := 0;
	repeat
		result := result + s;
		s := s + 1;
	until s >= 100;
	write(result);
end.