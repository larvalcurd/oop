using NUnit.Framework;

using Bodies;

namespace Bodies.Tests;

[TestFixture]
public class BodyUtilsTests
{
    [Test]
    public void FindBodyWithMaxMass_ReturnsHeaviestBody()
    {
        var light = new CSphere(100, 1);
        var heavy = new CParallelepiped(1000, 10, 10, 10);

        CBody? result = BodyUtils.FindBodyWithMaxMass(new CBody[] { light, heavy });

        Assert.That(result, Is.SameAs(heavy));
    }

    [Test]
    public void FindBodyWithMaxMass_ReturnsFirstBody_WhenMassesAreEqual()
    {
        var first = new CParallelepiped(1000, 1, 1, 1);
        var second = new CParallelepiped(1000, 1, 1, 1);

        CBody? result = BodyUtils.FindBodyWithMaxMass(new CBody[] { first, second });

        Assert.That(result, Is.SameAs(first));
    }

    [Test]
    public void FindBodyWithMaxMass_ReturnsNull_ForEmptyCollection()
    {
        CBody? result = BodyUtils.FindBodyWithMaxMass(Array.Empty<CBody>());

        Assert.That(result, Is.Null);
    }

    [Test]
    public void FindBodyWithMaxMass_Throws_ForNullCollection()
    {
        Assert.Throws<ArgumentNullException>(() => BodyUtils.FindBodyWithMaxMass(null!));
    }

    [Test]
    public void FindBodyWithMinWeightInWater_ReturnsCorrectBody()
    {
        var body1 = new CSphere(900, 1);
        var body2 = new CSphere(1100, 1);

        CBody? result = BodyUtils.FindBodyWithMinWeightInWater(new[] { body1, body2 });

        Assert.That(result, Is.SameAs(body1));
    }

    [Test]
    public void FindBodyWithMinWeightInWater_ReturnsFirstBody_WhenWeightsAreEqual()
    {
        var first = new CSphere(900, 1);
        var second = new CSphere(900, 1);

        CBody? result = BodyUtils.FindBodyWithMinWeightInWater(new CBody[] { first, second });

        Assert.That(result, Is.SameAs(first));
    }

    [Test]
    public void FindBodyWithMinWeightInWater_ReturnsNull_ForEmptyCollection()
    {
        CBody? result = BodyUtils.FindBodyWithMinWeightInWater(Array.Empty<CBody>());

        Assert.That(result, Is.Null);
    }

    [Test]
    public void FindBodyWithMinWeightInWater_Throws_ForNullCollection()
    {
        Assert.Throws<ArgumentNullException>(() => BodyUtils.FindBodyWithMinWeightInWater(null!));
    }
}
