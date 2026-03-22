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

    [Test]
    public void SetGear_ToMinus2_ReturnsFalse()
    {
        var car = new Car();
        car.TurnOnEngine();
        bool result = car.SetGear(-2);
        Assert.That(result, Is.False);
    }

    [Test]
    public void SetGear_AtExactBoundary_ReturnsTrue()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(20);

        bool result = car.SetGear(2);

        Assert.That(result, Is.True);
    }

    [Test]
    public void SetGear_AtExactBoundary_30_ToThird_ReturnsTrue()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);

        bool result = car.SetGear(3);

        Assert.That(result, Is.True);
    }

    [Test]
    public void SetGear_ToReverse_WhenMovingForward_ReturnsFalse()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);

        bool result = car.SetGear(-1);

        Assert.That(result, Is.False);
    }

    [Test]
    public void SetGear_ToReverse_WhenMovingBackwardOnNeutral_ReturnsFalse()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(-1);
        car.SetSpeed(15);
        car.SetGear(0);

        bool result = car.SetGear(-1);

        Assert.That(result, Is.False);
    }

    [Test]
    public void SetGear_ToFifth_AtSpeed50_ReturnsTrue()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        car.SetGear(3);
        car.SetSpeed(50);

        bool result = car.SetGear(5);

        Assert.That(result, Is.True);
    }

    [Test]
    public void SetSpeed_OnFifth_ToMax150_ReturnsTrue()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        car.SetGear(3);
        car.SetSpeed(50);
        car.SetGear(5);

        bool result = car.SetSpeed(150);

        Assert.That(result, Is.True);
    }

    [Test]
    public void SetSpeed_OnFifth_Above150_ReturnsFalse()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        car.SetGear(3);
        car.SetSpeed(50);
        car.SetGear(5);

        bool result = car.SetSpeed(151);

        Assert.That(result, Is.False);
    }

    [Test]
    public void SetGear_ToSameGear_ReturnsTrue()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);

        bool result = car.SetGear(1);

        Assert.That(result, Is.True);
    }
}
