using Calculator.Expressions;

namespace Calculator.Tests.Expressions;

public class IdentifierExpressionTests
{
    [Test]
    public void Evaluate_ExistingVariable_ReturnsItsValue()
    {
        var calculator = new Calculator();
        calculator.DeclareVariable("x");
        calculator.SetVariable("x", 5.0);
        
        var expression = new IdentifierExpression("x");
        
        double result = expression.Evaluate(calculator);
        
        Assert.That(result, Is.EqualTo(5.0));
    }
}