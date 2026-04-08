using Bodies;

namespace Bodies.Tests;

[TestFixture]
public class CCompoundTests
{
    [Test]
    public void NewCompound_IsEmpty()
    {
        var compound = new CCompound();

        Assert.Multiple(() =>
        {
            Assert.That(compound.GetVolume(), Is.EqualTo(0).Within(TestConstants.Epsilon));
            Assert.That(compound.GetMass(), Is.EqualTo(0).Within(TestConstants.Epsilon));
            Assert.That(compound.GetDensity(), Is.EqualTo(0).Within(TestConstants.Epsilon));
            Assert.That(compound.GetChildren().Count, Is.EqualTo(0));
        });
    }

    [Test]
    public void AddChildBody_AddsSimpleBody()
    {
        var compound = new CCompound();
        var sphere = new CSphere(1000, 1);

        bool result = compound.AddChildBody(sphere);

        Assert.Multiple(() =>
        {
            Assert.That(result, Is.True);
            Assert.That(compound.GetChildren().Count, Is.EqualTo(1));
            Assert.That(compound.GetChildren()[0], Is.SameAs(sphere));
        });
    }

    [Test]
    public void AddChildBody_CanContainAnotherCompound()
    {
        var inner = new CCompound();
        inner.AddChildBody(new CSphere(1000, 1));
        var outer = new CCompound();

        bool result = outer.AddChildBody(inner);

        Assert.Multiple(() =>
        {
            Assert.That(result, Is.True);
            Assert.That(outer.GetChildren().Count, Is.EqualTo(1));
            Assert.That(outer.GetChildren()[0], Is.SameAs(inner));
        });
    }

    [Test]
    public void AddChildBody_RejectsNull()
    {
        var compound = new CCompound();

        bool result = compound.AddChildBody(null!);

        Assert.That(result, Is.False);
    }

    [Test]
    public void AddChildBody_RejectsSelfReference()
    {
        var compound = new CCompound();

        bool result = compound.AddChildBody(compound);

        Assert.That(result, Is.False);
    }

    [Test]
    public void AddChildBody_RejectsDirectCycle()
    {
        var parent = new CCompound();
        var child = new CCompound();

        Assert.That(parent.AddChildBody(child), Is.True);
        Assert.That(child.AddChildBody(parent), Is.False);
    }

    [Test]
    public void AddChildBody_RejectsIndirectCycle()
    {
        var a = new CCompound();
        var b = new CCompound();
        var c = new CCompound();

        Assert.That(a.AddChildBody(b), Is.True);
        Assert.That(b.AddChildBody(c), Is.True);
        Assert.That(c.AddChildBody(a), Is.False);
    }

    [Test]
    public void ContainsBody_ReturnsExpectedResultForDirectNestedAndMissingBody()
    {
        var inner = new CCompound();
        var outer = new CCompound();
        var sphere = new CSphere(1000, 1);
        var missing = new CCylinder(1000, 1, 2);

        inner.AddChildBody(sphere);
        outer.AddChildBody(inner);

        Assert.Multiple(() =>
        {
            Assert.That(outer.ContainsBody(inner), Is.True);
            Assert.That(outer.ContainsBody(sphere), Is.True);
            Assert.That(outer.ContainsBody(missing), Is.False);
            Assert.That(outer.ContainsBody(null!), Is.False);
        });
    }

    [Test]
    public void GetVolumeMassDensity_AggregatesChildren()
    {
        var sphere = new CSphere(1000, 1);
        var box = new CParallelepiped(500, 2, 3, 4);
        var compound = new CCompound();
        compound.AddChildBody(sphere);
        compound.AddChildBody(box);

        double expectedVolume = sphere.GetVolume() + box.GetVolume();
        double expectedMass = sphere.GetMass() + box.GetMass();
        double expectedDensity = expectedMass / expectedVolume;

        Assert.Multiple(() =>
        {
            Assert.That(compound.GetVolume(), Is.EqualTo(expectedVolume).Within(TestConstants.Epsilon));
            Assert.That(compound.GetMass(), Is.EqualTo(expectedMass).Within(TestConstants.Epsilon));
            Assert.That(compound.GetDensity(), Is.EqualTo(expectedDensity).Within(TestConstants.Epsilon));
        });
    }

    [Test]
    public void ToString_ContainsChildrenCountAndMetrics()
    {
        var compound = new CCompound();
        compound.AddChildBody(new CSphere(1200, 1));
        string text = compound.ToString();

        Assert.That(text, Does.Contain("Compound:"));
        Assert.That(text, Does.Contain("Children = 1"));
        Assert.That(text, Does.Contain("Density ="));
        Assert.That(text, Does.Contain("Volume ="));
        Assert.That(text, Does.Contain("Mass ="));
    }
}
