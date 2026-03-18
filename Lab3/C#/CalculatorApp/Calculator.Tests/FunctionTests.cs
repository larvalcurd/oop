namespace Calculator.Tests.Functions;

[TestFixture]
public class DeclareFunction
{
    [Test]
    public void NewName_FunctionExists()
    {
        var calc = new Calculator();
        calc.DeclareVariable("x");
        
        calc.DeclareFunction("getX", "x");
        
        Assert.That(calc.FunctionExists("getX"), Is.True);
    }
    
    [Test]
    public void SameName_ThrowsException()
    {
        var calc = new Calculator();
        calc.DeclareVariable("x");
        calc.DeclareFunction("f", "x");
        
        Assert.Throws<InvalidOperationException>(() => calc.DeclareFunction("f", "x"));
    }
    
    [Test]
    public void VariableNameExists_ThrowsException()
    {
        var calc = new Calculator();
        calc.DeclareVariable("x");
        
        Assert.Throws<InvalidOperationException>(() => calc.DeclareFunction("x", "x"));
    }
}

[TestFixture]
public class GetValue_Functions
{
    [Test]
    public void SimpleFunction_ReturnsVariableValue()
    {
        var calc = new Calculator();
        calc.DeclareVariable("x");
        calc.SetVariable("x", 42.0);
        calc.DeclareFunction("getX", "x");
        
        Assert.That(calc.GetValue("getX"), Is.EqualTo(42.0));
    }
    
    [Test]
    public void FunctionWithBinaryExpression_ReturnsComputedValue()
    {
        var calc = new Calculator();
        calc.DeclareVariable("x");
        calc.DeclareVariable("y");
        calc.SetVariable("x", 3.0);
        calc.SetVariable("y", 4.0);
        calc.DeclareFunction("sum", "x", "+", "y");
        
        Assert.That(calc.GetValue("sum"), Is.EqualTo(7.0));
    }
    
    [Test]
    public void FunctionAfterVariableChange_ReturnsNewValue()
    {
        var calc = new Calculator();
        calc.DeclareVariable("x");
        calc.SetVariable("x", 10.0);
        calc.DeclareFunction("getX", "x");
        
        Assert.That(calc.GetValue("getX"), Is.EqualTo(10.0));
        
        calc.SetVariable("x", 99.0);
        
        Assert.That(calc.GetValue("getX"), Is.EqualTo(99.0));
    }
}