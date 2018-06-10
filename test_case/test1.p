program test1;

    type
        int = integer;
    var
        n1 : int;

    function max(num1:integer; num2:integer; xx:char):integer;
        var
            result:int;
    begin
        if (num1 < num2) then result := num2 else result := num1;
        max := result;
    end;

    function min(num1:integer; num2:integer):integer;
        var
            r : int;
    begin
        if (num1 > num2) then r := num2 else r := num1;
        min := r;
    end;

begin
    n1 := 1;
    n1 := max(2,3);
    write(n1);
end.