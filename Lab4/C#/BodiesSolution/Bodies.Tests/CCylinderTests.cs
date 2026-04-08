using Bodies;

namespace Bodies.Tests;

[TestFixture]
public class CCylinderTests
{
    [Test]
    public void Getters_ReturnCtorValues()
    {
        var cylinder = new CCylinder(1000, 2, 3);

        Assert.Multiple(() =>
        {
            Assert.That(cylinder.GetBaseRadius(), Is.EqualTo(2).Within(TestConstants.Epsilon));
            Assert.That(cylinder.GetHeight(), Is.EqualTo(3).Within(TestConstants.Epsilon));
        });
    }

    [Test]
    public void GetVolume_CalculatesExpectedValue()
    {
        var cylinder = new CCylinder(1000, 2, 3);
        double expected = Math.PI * 2 * 2 * 3;

        Assert.That(cylinder.GetVolume(), Is.EqualTo(expected).Within(TestConstants.Epsilon));
    }

    [Test]
    public void GetMass_IsDensityByVolume()
    {
        var cylinder = new CCylinder(10, 2, 3);
        double expected = 10 * Math.PI * 2 * 2 * 3;

        Assert.That(cylinder.GetMass(), Is.EqualTo(expected).Within(TestConstants.Epsilon));
    }

    [Test]
    public void Constructor_WithNonPositiveDimensions_Throws()
    {
        Assert.Throws<ArgumentException>(() => new CCylinder(1000, 0, 1));
        Assert.Throws<ArgumentException>(() => new CCylinder(1000, 1, 0));
    }

    [Test]
    public void ToString_ContainsShapeAndDimensions()
    {
        var cylinder = new CCylinder(750, 1.5, 5);
        string text = cylinder.ToString();

        Assert.That(text, Does.Contain("Cylinder:"));
        Assert.That(text, Does.Contain("BaseRadius = 1.500"));
        Assert.That(text, Does.Contain("Height = 5.000"));
        Assert.That(text, Does.Contain("Density = 750.000"));
    }
}
