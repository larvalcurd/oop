namespace Calculator.Tests;

public class CalculatorTests
{
    [Test]
    public void DeclareVariable_NewName_VariableExistsWithNaN()
    {
        var calculator = new Calculator();

        calculator.DeclareVariable("x");

        Assert.That(calculator.GetVariable("x").Value, Is.NaN);
    }

    [Test]
    public void DeclareVariable_NameAlreadyExists_ThrowsException()
    {
        var calculator = new Calculator();
        calculator.DeclareVariable("x");

        Assert.Throws<InvalidOperationException>(() => calculator.DeclareVariable("x"));
    }

    [Test]
    public void GetValue_ExistingVariable_ReturnsItsValue()
    {
        var calculator = new Calculator();
        calculator.DeclareVariable("x");
        calculator.SetVariable("x", 42.0);

        Assert.That(calculator.GetValue("x"), Is.EqualTo(42.0));
    }

    [Test]
    public void GetValue_NonExistingIdentifier_ThrowsException()
    {
        var calculator = new Calculator();

        Assert.Throws<KeyNotFoundException>(() => calculator.GetValue("unknown"));
    }
}

[TestFixture]
public class GetAllVariables
{
    [Test]
    public void ReturnsAllVariablesSortedByName()
    {
        var calc = new Calculator();
        calc.SetVariable("z", 3.0);
        calc.SetVariable("a", 1.0);
        calc.SetVariable("m", 2.0);

        var variables = calc.GetAllVariables().ToList();

        Assert.That(variables.Count, Is.EqualTo(3));
        Assert.That(variables[0].Name, Is.EqualTo("a"));
        Assert.That(variables[1].Name, Is.EqualTo("m"));
        Assert.That(variables[2].Name, Is.EqualTo("z"));
    }
}

[TestFixture]
public class GetAllFunctions
{
    [Test]
    public void ReturnsAllFunctionsSortedByName()
    {
        var calc = new Calculator();
        calc.SetVariable("x", 1.0);
        calc.DeclareFunction("zFunc", "x");
        calc.DeclareFunction("aFunc", "x");

        var functions = calc.GetAllFunctions().ToList();

        Assert.That(functions.Count, Is.EqualTo(2));
        Assert.That(functions[0].Name, Is.EqualTo("aFunc"));
        Assert.That(functions[1].Name, Is.EqualTo("zFunc"));
    }
}