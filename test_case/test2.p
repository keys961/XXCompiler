program test2;
    type
        int = integer;
    var
        n1 : int;
        n2 : int;
        n3 : int;
    procedure max(num1 : integer; num2 :integer);
        var
            result:int;
    begin
        result := num1;
    end;
begin
    n1 := 1;
    n2 := 2;
	max(n1,n2);
end.