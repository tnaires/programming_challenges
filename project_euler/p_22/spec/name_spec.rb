require './app/name'

describe Name do
  subject { Name.new('foo', 1) }

  it { subject.value.should == 'foo' }
  it { subject.position.should == 1 }

  describe :score do
    it { Name.new('foo', 1).score.should == 36 }
    it { Name.new('FOO', 2).score.should == 72 }
    it { Name.new('ALONSO', 147).score.should == 147 * (1 + 12 + 15 + 14 + 19 + 15) }
  end
end
