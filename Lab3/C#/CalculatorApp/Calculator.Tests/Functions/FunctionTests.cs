using NUnit.Framework;
using Calculator.Functions;
using Calculator.Expressions;

namespace Calculator.Tests.Functions;

public class FunctionTests
{
    [TestFixture]
    public class Constructor
    {
        [Test]
        public void WithValidName_StoresName()
        {
            var expression = new IdentifierExpression("x");
            
            var function = new Function("myFunc", expression);
            
            Assert.That(function.Name, Is.EqualTo("myFunc"));
        }
        
        [TestCase("")]
        [TestCase("123")]
        [TestCase("x-y")]
        public void WithInvalidName_ThrowsArgumentException(string invalidName)
        {
            var expression = new IdentifierExpression("x");
            
            Assert.Throws<ArgumentException>(() => new Function(invalidName, expression));
        }
    }
    
    [TestFixture]
    public class Evaluate
    {
        [Test]
        public void SimpleIdentifier_ReturnsVariableValue()
        {
            var calculator = new Calculator();
            calculator.DeclareVariable("x");
            calculator.SetVariable("x", 42.0);
            
            var function = new Function("getX", new IdentifierExpression("x"));
            
            Assert.That(function.Evaluate(calculator), Is.EqualTo(42.0));
        }
        
        [Test]
        public void AfterVariableChange_ReturnsNewValue()
        {
            var calculator = new Calculator();
            calculator.DeclareVariable("x");
            calculator.SetVariable("x", 10.0);
            
            var function = new Function("getX", new IdentifierExpression("x"));
            
            Assert.That(function.Evaluate(calculator), Is.EqualTo(10.0));
            
            calculator.SetVariable("x", 99.0);
            
            Assert.That(function.Evaluate(calculator), Is.EqualTo(99.0));
        }
        
        [Test]
        public void BinaryExpression_ReturnsComputedValue()
        {
            var calculator = new Calculator();
            calculator.DeclareVariable("x");
            calculator.DeclareVariable("y");
            calculator.SetVariable("x", 3.0);
            calculator.SetVariable("y", 4.0);
            
            var expression = new BinaryExpression(
                new IdentifierExpression("x"),
                new IdentifierExpression("y"),
                Operation.Add
            );
            var function = new Function("sum", expression);
            
            Assert.That(function.Evaluate(calculator), Is.EqualTo(7.0));
        }
    }
}