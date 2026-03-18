namespace Calculator.Tests;

public class VariableTests
{
    [Test]
    public void Constructor_WithVaalidName_ValueIsNan()
    {
        var variable = new Variable("x");

        Assert.That(variable.Value, Is.NaN);
    }

    [Test]
    public void Value_AfterAssignment_ReturnsAssignedValue()
    {
        var variable = new Variable("x");
        variable.Value = 42.0;

        Assert.That(variable.Value, Is.EqualTo(42.0));
    }

    [TestCase("")]
    [TestCase("   ")]
    [TestCase("123")]
    [TestCase("1abc")]
    [TestCase("x-y")]
    [TestCase("x.y")]
    [TestCase("привет")]
    public void Constructor_WithInvalidName_ThrowsArgumentException(string invalidName)
    {
        Assert.Throws<ArgumentException>(() => new Variable(invalidName));
    }

    [TestCase("x")]
    [TestCase("X")]
    [TestCase("_x")]
    [TestCase("x1")]
    [TestCase("myVariable")]
    [TestCase("MAX_VALUE")]
    [TestCase("_123")]
    public void Constructor_WithValidName_DoesNotThrow(string validName)
    {
        Assert.DoesNotThrow(() => new Variable(validName));
    }
}


