using Bodies;

namespace Bodies.Tests;

[TestFixture]
public class CSphereTests
{
    [Test]
    public void GetRadius_ReturnsCtorValue()
    {
        var sphere = new CSphere(500, 2);

        Assert.That(sphere.GetRadius(), Is.EqualTo(2).Within(TestConstants.Epsilon));
    }

    [Test]
    public void GetVolume_CalculatesExpectedValue()
    {
        var sphere = new CSphere(1000, 2);
        double expected = (4.0 / 3.0) * Math.PI * Math.Pow(2, 3);

        Assert.That(sphere.GetVolume(), Is.EqualTo(expected).Within(TestConstants.Epsilon));
    }

    [Test]
    public void GetMass_IsDensityByVolume()
    {
        var sphere = new CSphere(500, 2);
        double expected = 500 * ((4.0 / 3.0) * Math.PI * Math.Pow(2, 3));

        Assert.That(sphere.GetMass(), Is.EqualTo(expected).Within(TestConstants.Epsilon));
    }

    [Test]
    public void Constructor_WithNonPositiveRadius_Throws()
    {
        Assert.Throws<ArgumentException>(() => new CSphere(1000, 0));
        Assert.Throws<ArgumentException>(() => new CSphere(1000, -1));
    }

    [Test]
    public void Constructor_WithNonPositiveDensity_Throws()
    {
        Assert.Throws<ArgumentException>(() => new CSphere(0, 1));
        Assert.Throws<ArgumentException>(() => new CSphere(-1, 1));
    }

    [Test]
    public void ToString_ContainsShapeAndMainMetrics()
    {
        var sphere = new CSphere(1200, 1.5);
        string text = sphere.ToString();

        Assert.That(text, Does.Contain("Sphere:"));
        Assert.That(text, Does.Contain("Radius = 1.500"));
        Assert.That(text, Does.Contain("Density = 1200.000"));
        Assert.That(text, Does.Contain("Volume ="));
        Assert.That(text, Does.Contain("Mass ="));
    }
}
