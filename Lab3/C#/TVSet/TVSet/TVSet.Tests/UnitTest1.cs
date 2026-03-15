using System.Runtime.CompilerServices;
using NUnit.Framework;
using TVSetApp;
namespace TVSetApp.Tests;

[TestFixture]
public class TVSetTests
{
    [Test]
    public void TurnOn_TvBecomesTurnedOn()
    {
        var tvSet = new TVSet();

        tvSet.TurnOn();

        Assert.That(tvSet.IsOn, Is.True);
    }

    [Test]
    public void NewTV_isOff_ByDefault()
    {
        var tvSet = new TVSet();

        Assert.That(tvSet.IsOn, Is.False);
    }

    [Test]
    public void GetChannel_WhenOff_Returns_Zero()
    {
        var tvSet = new TVSet();

        Assert.That(tvSet.GetChannel(), Is.EqualTo(0));
    }

    [Test]
    public void TurnOn_FirstTime_ChannleIsOne()
    {
        var tvSet = new TVSet();

        tvSet.TurnOn();

        Assert.That(tvSet.GetChannel(), Is.EqualTo(1));
    }

    [Test]
    public void TurnOn_AfterWathchingChannle5_RemembersChannel()
    {
        var tvSet = new TVSet();
        tvSet.TurnOn();
        tvSet.SelectChannel(5);
        tvSet.TurnOff();

        tvSet.TurnOn();

        Assert.That(tvSet.GetChannel(), Is.EqualTo(5));
    }

    [Test]
    public void SelectChannel_InvalidChannel100_StaysOnCurrentChannel()
    {
        var tvSet = new TVSet();
        tvSet.TurnOn();
        tvSet.SelectChannel(5);

        tvSet.SelectChannel(100);

        Assert.That(tvSet.GetChannel(), Is.EqualTo(5));
    }

    [Test]
    public void SelectChannel_InvalidChannel0_StaysOnCurrentChannel()
    {
        var tvSet = new TVSet();
        tvSet.TurnOn();
        tvSet.SelectChannel(5);

        tvSet.SelectChannel(0);

        Assert.That(tvSet.GetChannel(), Is.EqualTo(5));
    }

    [Test]
    public void SelectChannel_NegativeChannel_StaysOnCurrentChannel()
    {
        var tvSet = new TVSet();
        tvSet.TurnOn();
        tvSet.SelectChannel(5);

        tvSet.SelectChannel(-1);

        Assert.That(tvSet.GetChannel(), Is.EqualTo(5));
    }

    [Test]
    public void SelectPreviousChannel_AfterSwitching_GoesBack()
    {
        var tvSet = new TVSet();
        tvSet.TurnOn();
        tvSet.SelectChannel(5);
        tvSet.SelectChannel(10);

        tvSet.SelectPreviousChannel();

        Assert.That(tvSet.GetChannel(), Is.EqualTo(5));
    }

    [Test]
    public void SelectPreviousChannel_CalledTwice_GoesBackToPrevious()
    {
        var tvSet = new TVSet();
        tvSet.TurnOn();
        tvSet.SelectChannel(5);
        tvSet.SelectChannel(10);

        tvSet.SelectPreviousChannel();
        tvSet.SelectPreviousChannel();

        Assert.That(tvSet.GetChannel(), Is.EqualTo(10));
    }

    [Test]
    public void SelectPreviousChannel_WhenOff_DoesNothing()
    {
        var tvSet = new TVSet();
        tvSet.TurnOn();
        tvSet.SelectChannel(5);
        tvSet.SelectChannel(10);
        tvSet.TurnOff();

        tvSet.SelectPreviousChannel();
        tvSet.TurnOn();

        Assert.That(tvSet.GetChannel(), Is.EqualTo(10));
    }

    [Test]
    public void SelectPreviousChannel_NoPreviousChannel_StaysOnCurrentChannel()
    {
        var tvSet = new TVSet();
        tvSet.TurnOn();

        tvSet.SelectPreviousChannel();

        Assert.That(tvSet.GetChannel(), Is.EqualTo(1));
    }

    [Test]
    public void SetChannelName_ValidName_CanGetByNumber()
    {
        var tvSet = new TVSet();
        tvSet.TurnOn();

        tvSet.SetChannelName(5, "News");

        Assert.That(tvSet.GetChannelName(5), Is.EqualTo("News"));
    }

    [Test]
    public void GetChannleBYName_AfterSetName_ReturnsChannelNumber()
    {
        var tvSet = new TVSet();
        tvSet.TurnOn();

        tvSet.SetChannelName(5, "News");

        Assert.That(tvSet.GetChannelByName("News"), Is.EqualTo(5));
    }

    [Test]
    public void SelectChannel_ByName_SwitchesToCorrectChannel()
    {
        var tvSet = new TVSet();
        tvSet.TurnOn();
        tvSet.SetChannelName(5, "News");

        tvSet.SelectChannel("News");

        Assert.That(tvSet.GetChannel(), Is.EqualTo(5));
    }

    [Test]
    public void DeleteChannelName_ExistingName_RemovesName()
    {
        var tvSet = new TVSet();
        tvSet.TurnOn();
        tvSet.SetChannelName(5, "News");

        bool result = tvSet.DeleteChannelName("News");

        Assert.That(result, Is.True);
        Assert.That(tvSet.GetChannelName(5), Is.Null);
        Assert.That(tvSet.GetChannelByName("News"), Is.EqualTo(0));
    }

    [Test]
    public void DeleteChannelName_NonExistingName_ReturnsFalse()
    {
        var tvSet = new TVSet();
        tvSet.TurnOn();

        bool result = tvSet.DeleteChannelName("NoSuchChannel");

        Assert.That(result, Is.False);
    }

    [Test]
    public void SetChannelName_NameAlreadyUsed_MovesToNewChannel()
    {
        var tvSet = new TVSet();
        tvSet.TurnOn();
        tvSet.SetChannelName(5, "News");

        tvSet.SetChannelName(10, "News");

        Assert.That(tvSet.GetChannelByName("News"), Is.EqualTo(10));
        Assert.That(tvSet.GetChannelName(5), Is.Null);
    }
    [Test]
    public void SetChannelName_ChannelHadOtherName_ReplacesIt()
    {
        var tvSet = new TVSet();
        tvSet.TurnOn();
        tvSet.SetChannelName(5, "News");

        tvSet.SetChannelName(5, "Sports");

        Assert.That(tvSet.GetChannelName(5), Is.EqualTo("Sports"));
        Assert.That(tvSet.GetChannelByName("News"), Is.EqualTo(0));
    }

    [Test]
    public void SetChannelName_WhenOff_ReturnsFalse()
    {
        var tvSet = new TVSet();

        bool result = tvSet.SetChannelName(5, "News");

        Assert.That(result, Is.False);
    }

    [Test]
    public void SelectChannelByName_WhenOff_DoesNothing()
    {
        var tvSet = new TVSet();
        tvSet.TurnOn();
        tvSet.SetChannelName(5, "News");
        tvSet.TurnOff();

        tvSet.SelectChannel("News");

        Assert.That(tvSet.GetChannel(), Is.EqualTo(0));
    }
}
