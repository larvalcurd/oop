using Bodies;

namespace Bodies.Tests;

[TestFixture]
public class CParallelepipedTests
{
    [Test]
    public void Getters_ReturnCtorDimensions()
    {
        var body = new CParallelepiped(1000, 2, 3, 4);

        Assert.Multiple(() =>
        {
            Assert.That(body.GetWidth(), Is.EqualTo(2).Within(TestConstants.Epsilon));
            Assert.That(body.GetHeight(), Is.EqualTo(3).Within(TestConstants.Epsilon));
            Assert.That(body.GetDepth(), Is.EqualTo(4).Within(TestConstants.Epsilon));
        });
    }

    [Test]
    public void GetVolume_CalculatesExpectedValue()
    {
        var body = new CParallelepiped(1000, 2, 3, 4);

        Assert.That(body.GetVolume(), Is.EqualTo(24).Within(TestConstants.Epsilon));
    }

    [Test]
    public void GetMass_IsDensityByVolume()
    {
        var body = new CParallelepiped(10, 2, 3, 4);

        Assert.That(body.GetMass(), Is.EqualTo(240).Within(TestConstants.Epsilon));
    }

    [Test]
    public void Constructor_WithNonPositiveDimensions_Throws()
    {
        Assert.Throws<ArgumentException>(() => new CParallelepiped(1000, 0, 1, 1));
        Assert.Throws<ArgumentException>(() => new CParallelepiped(1000, 1, 0, 1));
        Assert.Throws<ArgumentException>(() => new CParallelepiped(1000, 1, 1, 0));
    }

    [Test]
    public void ToString_ContainsShapeAndDimensions()
    {
        var body = new CParallelepiped(300, 2, 3, 4);
        string text = body.ToString();

        Assert.That(text, Does.Contain("Parallelepiped:"));
        Assert.That(text, Does.Contain("Width = 2.000"));
        Assert.That(text, Does.Contain("Height = 3.000"));
        Assert.That(text, Does.Contain("Depth = 4.000"));
        Assert.That(text, Does.Contain("Density = 300.000"));
    }
}
