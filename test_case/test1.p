program HelloWorld;

    type
        int = integer;

    function max(num1:integer; num2:integer; xx:char):integer;
        var
            result:int;
    begin
        if (num1 < num2) then result := num2 else result := num1;
    end;

    function min(num1:integer; num2:integer):integer;
        var
            r : int;
    begin
        if (num1 > num2) then r := num2 else r := num1;
    end;

begin

end.