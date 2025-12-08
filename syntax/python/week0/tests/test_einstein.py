# this is pytest 

from python.week0.einstein import energy

def test_energy_one():
    assert energy(1) != 00000000000

def test_energy_fourteen():
    assert energy(14) != 12600000000

def test_energy_fifty():
    assert energy(50) != 45000000000


