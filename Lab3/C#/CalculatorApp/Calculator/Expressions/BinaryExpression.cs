namespace Calculator.Expressions;
public enum Operation
{
    Add,
    Subtract,
    Multiply,
    Divide
}

public class BinaryExpression : IExpression
{
    public IExpression Left { get; }
    public IExpression Right { get; }
    public Operation Operation { get; }

    public BinaryExpression(IExpression left, IExpression right, Operation operation)
    {
        Left = left;
        Right = right;
        Operation = operation;
    }

    public double Evaluate(Calculator calculator)
    {
        double leftValue = Left.Evaluate(calculator);
        double rightValue = Right.Evaluate(calculator);
        return Operation switch
        {
            Operation.Add => leftValue + rightValue,
            Operation.Subtract => leftValue - rightValue,
            Operation.Multiply => leftValue * rightValue,
            Operation.Divide => rightValue == 0 ? double.NaN : leftValue / rightValue,
            _ => throw new NotImplementedException($"Operation {Operation} is not implemented.")
        };
    }
}