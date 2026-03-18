
using System.Text.RegularExpressions;
using Calculator.Expressions;
namespace Calculator.Functions;

public class Function
{
    private static readonly Regex ValidNameRegex = new(@"^[a-zA-Z_][a-zA-Z0-9_]*$");
    public string Name { get; }
    private readonly IExpression _expression;

    public Function(string name, IExpression expression)
    {
        Identifier.Validate(name);
        Name = name;
        _expression = expression ?? throw new ArgumentNullException(nameof(expression));
    }

    public double Evaluate(Calculator calculator)
    {
        if (calculator == null) throw new ArgumentNullException(nameof(calculator));
        return _expression.Evaluate(calculator);
    }
}