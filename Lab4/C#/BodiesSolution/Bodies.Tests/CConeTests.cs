using Bodies;

namespace Bodies.Tests;

[TestFixture]
public class CConeTests
{
    [Test]
    public void Getters_ReturnCtorValues()
    {
        var cone = new CCone(1000, 2, 3);

        Assert.Multiple(() =>
        {
            Assert.That(cone.GetBaseRadius(), Is.EqualTo(2).Within(TestConstants.Epsilon));
            Assert.That(cone.GetHeight(), Is.EqualTo(3).Within(TestConstants.Epsilon));
        });
    }

    [Test]
    public void GetVolume_CalculatesExpectedValue()
    {
        var cone = new CCone(1000, 2, 3);
        double expected = Math.PI * 2 * 2 * 3 / 3.0;

        Assert.That(cone.GetVolume(), Is.EqualTo(expected).Within(TestConstants.Epsilon));
    }

    [Test]
    public void GetMass_IsDensityByVolume()
    {
        var cone = new CCone(10, 2, 3);
        double expected = 10 * (Math.PI * 2 * 2 * 3 / 3.0);

        Assert.That(cone.GetMass(), Is.EqualTo(expected).Within(TestConstants.Epsilon));
    }

    [Test]
    public void Constructor_WithNonPositiveDimensions_Throws()
    {
        Assert.Throws<ArgumentException>(() => new CCone(1000, 0, 1));
        Assert.Throws<ArgumentException>(() => new CCone(1000, 1, 0));
    }

    [Test]
    public void ToString_ContainsShapeAndDimensions()
    {
        var cone = new CCone(500, 1.25, 3.5);
        string text = cone.ToString();

        Assert.That(text, Does.Contain("Cone:"));
        Assert.That(text, Does.Contain("BaseRadius = 1.250"));
        Assert.That(text, Does.Contain("Height = 3.500"));
        Assert.That(text, Does.Contain("Density = 500.000"));
    }
}
