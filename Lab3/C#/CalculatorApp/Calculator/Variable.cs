using System.Text.RegularExpressions;

namespace Calculator;

public class Variable
{
    private static readonly Regex ValidNameRegex = new(@"^[a-zA-Z_][a-zA-Z0-9_]*$");
    public string Name { get; }
    public double Value { get; set; }

    public Variable(string name)
    {
        Identifier.Validate(name);
        Name = name;
        Value = double.NaN;
    }
}