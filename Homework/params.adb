with Text_IO; use Text_IO;
with Ada.Integer_Text_IO;
use Ada.Integer_Text_IO;

procedure params is
    procedure q is
        type IntFunc is access function (n:integer) return integer;
        m: integer := 0;

        function f (n: integer) return integer is
        begin 
            return m+n;
        end f;

        procedure p (g: IntFunc) is
            m: integer := 3;
        begin
            put(g(2)); new_line;
        end p;

    begin
        p(f' access);
    end q;

begin 
    q;
end params;


