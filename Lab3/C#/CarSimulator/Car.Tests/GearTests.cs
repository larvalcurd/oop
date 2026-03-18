namespace Car.Tests;

public class GearTests
{
    [Test]
    public void SetGear_EngineOff_ToNeutral_ReturnsTrue()
    {
        var car = new Car();
        bool result = car.SetGear(0);
        Assert.That(result, Is.True);
    }

    [Test]
    public void SetGear_EngineOff_ToFirst_ReturnsFalse()
    {
        var car = new Car();
        bool result = car.SetGear(1);
        Assert.That(result, Is.False);
    }

    [Test]
    public void SetGear_EngineOn_ToFirst_ReturnsTrue()
    {
        var car = new Car();
        car.TurnOnEngine();
        bool result = car.SetGear(1);
        Assert.That(result, Is.True);
        Assert.That(car.GetGear(), Is.EqualTo(Gear.First));
    }

    [Test]
    public void SetGear_InvalidGear_ReturnsFalse()
    {
        var car = new Car();
        car.TurnOnEngine();
        bool result = car.SetGear(6);
        Assert.That(result, Is.False);
    }

    [Test]
    public void SetGear_ToReverse_WhenStopped_ReturnsTrue()
    {
        var car = new Car();
        car.TurnOnEngine();
        bool result = car.SetGear(-1);
        Assert.That(result, Is.True);
        Assert.That(car.GetGear(), Is.EqualTo(Gear.Reverse));
    }

    [Test]
    public void SetGear_FromReverseToFirst_WhenMoving_ReturnsFalse()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(-1);
        car.SetSpeed(10);
        bool result = car.SetGear(1);
        Assert.That(result, Is.False);
        Assert.That(car.GetGear(), Is.EqualTo(Gear.Reverse));
    }

    [Test]
    public void SetGear_FromReverseToFirst_WhenStopped_ReturnsTrue()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(-1);
        car.SetSpeed(10);
        car.SetSpeed(0);
        bool result = car.SetGear(1);
        Assert.That(result, Is.True);
    }

    [Test]
    public void SetGear_FromNeutralToFirst_WhenMovingBackward_ReturnsFalse()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(-1);
        car.SetSpeed(10);
        car.SetGear(0);
        bool result = car.SetGear(1);
        Assert.That(result, Is.False);
    }

    [Test]
    public void SetGear_SpeedOutOfNewGearRange_ReturnsFalse()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(15);
        bool result = car.SetGear(2);
        Assert.That(result, Is.False);
    }

    [Test]
    public void SetGear_SpeedInNewGearRange_ReturnsTrue()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(25);
        bool result = car.SetGear(2);
        Assert.That(result, Is.True);
        Assert.That(car.GetGear(), Is.EqualTo(Gear.Second));
    }

    [Test]
    public void Example5_CannotSetGearOutOfSpeedRange()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(19);
        bool result = car.SetGear(2);
        Assert.That(result, Is.False);
        Assert.That(car.GetGear(), Is.EqualTo(Gear.First));
    }
}
