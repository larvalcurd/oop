using Calculator.Expressions;

namespace Calculator.Tests.Expressions;

public class BinaryExpressionTests
{
    [Test]
    public void Evaluate_AddTwoVariables_ReturnsSum()
    {
        var calculator = new Calculator();
        calculator.DeclareVariable("x");
        calculator.DeclareVariable("y");
        calculator.SetVariable("x", 3.0);
        calculator.SetVariable("y", 4.0);

        var left = new IdentifierExpression("x");
        var right = new IdentifierExpression("y");
        var expression = new BinaryExpression(left, right, Operation.Add);

        double result = expression.Evaluate(calculator);

        Assert.That(result, Is.EqualTo(7.0));
    }

    [Test]
    public void Evaluate_Subtract_ReturnsDifference()
    {
        var calculator = new Calculator();
        calculator.DeclareVariable("x");
        calculator.DeclareVariable("y");
        calculator.SetVariable("x", 10.0);
        calculator.SetVariable("y", 3.0);

        var expression = new BinaryExpression(
            new IdentifierExpression("x"),
            new IdentifierExpression("y"),
            Operation.Subtract
        );

        Assert.That(expression.Evaluate(calculator), Is.EqualTo(7.0));
    }

    [Test]
    public void Evaluate_Multiply_ReturnsProduct()
    {
        var calculator = new Calculator();
        calculator.DeclareVariable("x");
        calculator.DeclareVariable("y");
        calculator.SetVariable("x", 3.0);
        calculator.SetVariable("y", 4.0);

        var expression = new BinaryExpression(
            new IdentifierExpression("x"),
            new IdentifierExpression("y"),
            Operation.Multiply
        );

        Assert.That(expression.Evaluate(calculator), Is.EqualTo(12.0));
    }

    [Test]
    public void Evaluate_Divide_ReturnsQuotient()
    {
        var calculator = new Calculator();
        calculator.DeclareVariable("x");
        calculator.DeclareVariable("y");
        calculator.SetVariable("x", 20.0);
        calculator.SetVariable("y", 4.0);

        var expression = new BinaryExpression(
            new IdentifierExpression("x"),
            new IdentifierExpression("y"),
            Operation.Divide
        );

        Assert.That(expression.Evaluate(calculator), Is.EqualTo(5.0));
    }

    [Test]
    public void Evaluate_DivideByZero_ReturnsNaN()
    {
        var calculator = new Calculator();
        calculator.DeclareVariable("x");
        calculator.DeclareVariable("y");
        calculator.SetVariable("x", 10.0);
        calculator.SetVariable("y", 0.0);

        var expression = new BinaryExpression(
            new IdentifierExpression("x"),
            new IdentifierExpression("y"),
            Operation.Divide
        );

        Assert.That(expression.Evaluate(calculator), Is.NaN);
    }

    [Test]
    public void Evaluate_LeftOperandIsNaN_ReturnsNaN()
    {
        var calculator = new Calculator();
        calculator.DeclareVariable("x");  
        calculator.DeclareVariable("y");
        calculator.SetVariable("y", 5.0);

        var expression = new BinaryExpression(
            new IdentifierExpression("x"),
            new IdentifierExpression("y"),
            Operation.Add
        );

        Assert.That(expression.Evaluate(calculator), Is.NaN);
    }
}