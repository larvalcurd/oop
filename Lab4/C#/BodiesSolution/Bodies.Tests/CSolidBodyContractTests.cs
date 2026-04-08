using Bodies;

namespace Bodies.Tests;

[TestFixture]
public class CSolidBodyContractTests
{
    [Test]
    public void GetDensity_ReturnsCtorDensity_ForAllSimpleBodies()
    {
        var bodies = new CBody[]
        {
            new CSphere(321, 1),
            new CParallelepiped(654, 1, 2, 3),
            new CCone(987, 1, 2),
            new CCylinder(432, 1, 2)
        };

        Assert.Multiple(() =>
        {
            Assert.That(bodies[0].GetDensity(), Is.EqualTo(321).Within(TestConstants.Epsilon));
            Assert.That(bodies[1].GetDensity(), Is.EqualTo(654).Within(TestConstants.Epsilon));
            Assert.That(bodies[2].GetDensity(), Is.EqualTo(987).Within(TestConstants.Epsilon));
            Assert.That(bodies[3].GetDensity(), Is.EqualTo(432).Within(TestConstants.Epsilon));
        });
    }

    [Test]
    public void GetMass_EqualsDensityByVolume_ForAllSimpleBodies()
    {
        var bodies = new CBody[]
        {
            new CSphere(100, 1),
            new CParallelepiped(200, 1, 2, 3),
            new CCone(300, 1, 2),
            new CCylinder(400, 1, 2)
        };

        foreach (var body in bodies)
        {
            Assert.That(
                body.GetMass(),
                Is.EqualTo(body.GetDensity() * body.GetVolume()).Within(TestConstants.Epsilon));
        }
    }
}
