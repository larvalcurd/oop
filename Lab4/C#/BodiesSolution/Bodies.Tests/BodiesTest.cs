using NUnit.Framework;
using Bodies;

namespace Bodies.Tests;

[TestFixture]
public class BodiesTests
{
    private const double Epsilon = 1e-6;

    [Test]
    public void Sphere_ReturnsCorrectRadius()
    {
        var sphere = new CSphere(500, 2);

        Assert.That(sphere.GetRadius(), Is.EqualTo(2).Within(Epsilon));
    }

    [Test]
    public void Sphere_CalculatesVolumeCorrectly()
    {
        var sphere = new CSphere(1000, 2);

        double expectedVolume = 4.0 / 3.0 * Math.PI * Math.Pow(2, 3);

        Assert.That(sphere.GetVolume(), Is.EqualTo(expectedVolume).Within(Epsilon));
    }

    [Test]
    public void Sphere_CalculatesMassCorrectly()
    {
        var sphere = new CSphere(500, 2);

        double expectedVolume = 4.0 / 3.0 * Math.PI * Math.Pow(2, 3);
        double expectedMass = 500 * expectedVolume;

        Assert.That(sphere.GetMass(), Is.EqualTo(expectedMass).Within(Epsilon));
    }

    [Test]
    public void Parallelepiped_ReturnsCorrectDimensions()
    {
        var body = new CParallelepiped(1000, 2, 3, 4);

        Assert.That(body.GetWidth(), Is.EqualTo(2).Within(Epsilon));
        Assert.That(body.GetHeight(), Is.EqualTo(3).Within(Epsilon));
        Assert.That(body.GetDepth(), Is.EqualTo(4).Within(Epsilon));
    }

    [Test]
    public void Parallelepiped_CalculatesVolumeCorrectly()
    {
        var body = new CParallelepiped(1000, 2, 3, 4);

        Assert.That(body.GetVolume(), Is.EqualTo(24).Within(Epsilon));
    }

    [Test]
    public void Parallelepiped_CalculatesMassCorrectly()
    {
        var body = new CParallelepiped(10, 2, 3, 4);

        Assert.That(body.GetMass(), Is.EqualTo(240).Within(Epsilon));
    }

    [Test]
    public void Cone_ReturnsCorrectDimensions()
    {
        var cone = new CCone(1000, 2, 3);

        Assert.That(cone.GetBaseRadius(), Is.EqualTo(2).Within(Epsilon));
        Assert.That(cone.GetHeight(), Is.EqualTo(3).Within(Epsilon));
    }

    [Test]
    public void Cone_CalculatesVolumeCorrectly()
    {
        var cone = new CCone(1000, 2, 3);

        double expectedVolume = Math.PI * 2 * 2 * 3 / 3.0;

        Assert.That(cone.GetVolume(), Is.EqualTo(expectedVolume).Within(Epsilon));
    }

    [Test]
    public void Cone_CalculatesMassCorrectly()
    {
        var cone = new CCone(10, 2, 3);

        double expectedVolume = Math.PI * 2 * 2 * 3 / 3.0;
        double expectedMass = 10 * expectedVolume;

        Assert.That(cone.GetMass(), Is.EqualTo(expectedMass).Within(Epsilon));
    }

    [Test]
    public void Cylinder_ReturnsCorrectDimensions()
    {
        var cylinder = new CCylinder(1000, 2, 3);

        Assert.That(cylinder.GetBaseRadius(), Is.EqualTo(2).Within(Epsilon));
        Assert.That(cylinder.GetHeight(), Is.EqualTo(3).Within(Epsilon));
    }

    [Test]
    public void Cylinder_CalculatesVolumeCorrectly()
    {
        var cylinder = new CCylinder(1000, 2, 3);

        double expectedVolume = Math.PI * 2 * 2 * 3;

        Assert.That(cylinder.GetVolume(), Is.EqualTo(expectedVolume).Within(Epsilon));
    }

    [Test]
    public void Cylinder_CalculatesMassCorrectly()
    {
        var cylinder = new CCylinder(10, 2, 3);

        double expectedVolume = Math.PI * 2 * 2 * 3;
        double expectedMass = 10 * expectedVolume;

        Assert.That(cylinder.GetMass(), Is.EqualTo(expectedMass).Within(Epsilon));
    }

    [Test]
    public void Compound_IsEmptyInitially()
    {
        var compound = new CCompound();

        Assert.That(compound.GetVolume(), Is.EqualTo(0).Within(Epsilon));
        Assert.That(compound.GetMass(), Is.EqualTo(0).Within(Epsilon));
        Assert.That(compound.GetDensity(), Is.EqualTo(0).Within(Epsilon));
        Assert.That(compound.GetChildren().Count, Is.EqualTo(0));
    }

    [Test]
    public void Compound_AddChildBody_AddsSimpleBody()
    {
        var compound = new CCompound();
        var sphere = new CSphere(1000, 1);

        bool result = compound.AddChildBody(sphere);

        Assert.That(result, Is.True);
        Assert.That(compound.GetChildren().Count, Is.EqualTo(1));
        Assert.That(compound.GetChildren()[0], Is.SameAs(sphere));
    }

    [Test]
    public void Compound_CalculatesVolumeMassAndDensityCorrectly()
    {
        var sphere = new CSphere(1000, 1);
        var box = new CParallelepiped(500, 2, 3, 4);

        var compound = new CCompound();
        compound.AddChildBody(sphere);
        compound.AddChildBody(box);

        double expectedVolume = sphere.GetVolume() + box.GetVolume();
        double expectedMass = sphere.GetMass() + box.GetMass();
        double expectedDensity = expectedMass / expectedVolume;

        Assert.That(compound.GetVolume(), Is.EqualTo(expectedVolume).Within(Epsilon));
        Assert.That(compound.GetMass(), Is.EqualTo(expectedMass).Within(Epsilon));
        Assert.That(compound.GetDensity(), Is.EqualTo(expectedDensity).Within(Epsilon));
    }

    [Test]
    public void Compound_CanContainAnotherCompound()
    {
        var innerCompound = new CCompound();
        innerCompound.AddChildBody(new CSphere(1000, 1));

        var outerCompound = new CCompound();

        bool result = outerCompound.AddChildBody(innerCompound);

        Assert.That(result, Is.True);
        Assert.That(outerCompound.GetChildren().Count, Is.EqualTo(1));
        Assert.That(outerCompound.GetChildren()[0], Is.SameAs(innerCompound));
    }

    [Test]
    public void Compound_CannotAddNull()
    {
        var compound = new CCompound();

        bool result = compound.AddChildBody(null!);

        Assert.That(result, Is.False);
    }

    [Test]
    public void Compound_CannotAddItself()
    {
        var compound = new CCompound();

        bool result = compound.AddChildBody(compound);

        Assert.That(result, Is.False);
    }

    [Test]
    public void Compound_CannotCreateDirectCycle()
    {
        var parent = new CCompound();
        var child = new CCompound();

        Assert.That(parent.AddChildBody(child), Is.True);
        Assert.That(child.AddChildBody(parent), Is.False);
    }

    [Test]
    public void Compound_CannotCreateIndirectCycle()
    {
        var a = new CCompound();
        var b = new CCompound();
        var c = new CCompound();

        Assert.That(a.AddChildBody(b), Is.True);
        Assert.That(b.AddChildBody(c), Is.True);
        Assert.That(c.AddChildBody(a), Is.False);
    }

    [Test]
    public void Compound_ContainsBody_ReturnsTrueForDirectChild()
    {
        var compound = new CCompound();
        var sphere = new CSphere(1000, 1);

        compound.AddChildBody(sphere);

        Assert.That(compound.ContainsBody(sphere), Is.True);
    }

    [Test]
    public void Compound_ContainsBody_ReturnsTrueForNestedChild()
    {
        var inner = new CCompound();
        var outer = new CCompound();
        var sphere = new CSphere(1000, 1);

        inner.AddChildBody(sphere);
        outer.AddChildBody(inner);

        Assert.That(outer.ContainsBody(sphere), Is.True);
    }

    [Test]
    public void Compound_ContainsBody_ReturnsFalseIfBodyNotInside()
    {
        var compound = new CCompound();
        var sphere = new CSphere(1000, 1);

        Assert.That(compound.ContainsBody(sphere), Is.False);
    }

    [Test]
    public void FindBodyWithMaxMass_ReturnsHeaviestBody()
    {
        var light = new CSphere(100, 1);
        var heavy = new CParallelepiped(1000, 10, 10, 10);

        var result = BodyUtils.FindBodyWithMaxMass(new CBody[] { light, heavy });

        Assert.That(result, Is.SameAs(heavy));
    }

    [Test]
    public void FindBodyWithMaxMass_ReturnsNullForEmptyCollection()
    {
        var result = BodyUtils.FindBodyWithMaxMass(Array.Empty<CBody>());

        Assert.That(result, Is.Null);
    }

    [Test]
    public void FindBodyWithMinWeightInWater_ReturnsCorrectBody()
    {
        var body1 = new CSphere(900, 1);
        var body2 = new CSphere(1100, 1);

        var result = BodyUtils.FindBodyWithMinWeightInWater(new[] { body1, body2 });

        Assert.That(result, Is.SameAs(body1));
    }

    [Test]
    public void FindBodyWithMinWeightInWater_ReturnsNullForEmptyCollection()
    {
        var result = BodyUtils.FindBodyWithMinWeightInWater(Array.Empty<CBody>());

        Assert.That(result, Is.Null);
    }

    [Test]
    public void Sphere_WithNonPositiveRadius_ThrowsException()
    {
        Assert.Throws<ArgumentException>(() => new CSphere(1000, 0));
        Assert.Throws<ArgumentException>(() => new CSphere(1000, -1));
    }

    [Test]
    public void Parallelepiped_WithNonPositiveDimensions_ThrowsException()
    {
        Assert.Throws<ArgumentException>(() => new CParallelepiped(1000, 0, 1, 1));
        Assert.Throws<ArgumentException>(() => new CParallelepiped(1000, 1, 0, 1));
        Assert.Throws<ArgumentException>(() => new CParallelepiped(1000, 1, 1, 0));
    }

    [Test]
    public void Cone_WithNonPositiveDimensions_ThrowsException()
    {
        Assert.Throws<ArgumentException>(() => new CCone(1000, 0, 1));
        Assert.Throws<ArgumentException>(() => new CCone(1000, 1, 0));
    }

    [Test]
    public void Cylinder_WithNonPositiveDimensions_ThrowsException()
    {
        Assert.Throws<ArgumentException>(() => new CCylinder(1000, 0, 1));
        Assert.Throws<ArgumentException>(() => new CCylinder(1000, 1, 0));
    }

    [Test]
    public void SolidBody_WithNonPositiveDensity_ThrowsException()
    {
        Assert.Throws<ArgumentException>(() => new CSphere(0, 1));
        Assert.Throws<ArgumentException>(() => new CSphere(-1, 1));
    }
}