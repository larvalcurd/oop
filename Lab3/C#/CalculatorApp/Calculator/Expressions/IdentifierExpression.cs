namespace Calculator.Expressions;

public class IdentifierExpression : IExpression
{
    public string Name { get; }

    public IdentifierExpression(string name)
    {
        Name = name;
    }

    public double Evaluate(Calculator calculator)
    {
        return calculator.GetValue(Name);
    }
}