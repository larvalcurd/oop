using Bodies;

namespace Bodies.Tests;

[TestFixture]
public class CBodyCommonBehaviorTests
{
    [Test]
    public void GetWeightInWater_IsNegative_WhenDensityIsLowerThanWater()
    {
        var body = new CSphere(900, 1);

        Assert.That(body.GetWeightInWater(), Is.LessThan(0));
    }

    [Test]
    public void GetWeightInWater_IsZero_WhenDensityEqualsWater()
    {
        var body = new CSphere(1000, 2);

        Assert.That(body.GetWeightInWater(), Is.EqualTo(0).Within(TestConstants.Epsilon));
    }

    [Test]
    public void GetWeightInWater_IsPositive_WhenDensityIsHigherThanWater()
    {
        var body = new CSphere(1200, 1);

        Assert.That(body.GetWeightInWater(), Is.GreaterThan(0));
    }

    [Test]
    public void GetWeightInWater_ForCompound_UsesAverageDensityAndTotalVolume()
    {
        var compound = new CCompound();
        compound.AddChildBody(new CSphere(900, 1));
        compound.AddChildBody(new CSphere(1100, 1));

        double expected = (compound.GetDensity() - 1000) * compound.GetVolume();

        Assert.That(compound.GetWeightInWater(), Is.EqualTo(expected).Within(TestConstants.Epsilon));
    }
}
