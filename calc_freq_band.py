import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button, RadioButtons
from scipy import signal

#this program is made for discribing the frequency band of multiple feedback filter.#
#the circuit of this filter is here. http://sim.okawa-denshi.jp/OPttool.php #

C1 = 0.0000000000029
C2 = 0.000000000660
R1 = 100
R2 = 100
R3 = 50000
fig, ax = plt.subplots()
plt.subplots_adjust(left=0.25, bottom=0.35)
num = [-1/(C1 * R1), 0]          #bunsi
den = [1, 1/(C2 * R3) + 1/(C1 * R3), 1/(R3 * C1* C2)*(1/R1 + 1/R2)]   #bunbo
G   = signal.lti(num, den)
w, mag, phase = signal.bode(G, w = np.arange(1E+6, 1E+10, 1E+4))
l, = plt.semilogx(w, mag, lw=2, color='red')
plt.grid()
plt.ylim(-80, 150)
plt.xlim(1E+6, 1E+11)

axcolor = 'lightgoldenrodyellow'
axC1 = plt.axes([0.25, 0.0, 0.65, 0.03], facecolor=axcolor)
axC2 = plt.axes([0.25, 0.05, 0.65, 0.03], facecolor=axcolor)
axR1  = plt.axes([0.25, 0.10, 0.65, 0.03], facecolor=axcolor)
axR2 = plt.axes([0.25, 0.15, 0.65, 0.03], facecolor=axcolor)
axR3 = plt.axes([0.25, 0.20, 0.65, 0.03], facecolor=axcolor)

sC1 = Slider(axC1, 'C1', 0.0, 1000, valinit=2.90)
sC2 = Slider(axC2, 'C2', 0.0, 1000, valinit=660)
sR1 = Slider(axR1, 'R1', 100, 10000, valinit=100)
sR2 = Slider(axR2, 'R2', 100, 100000, valinit=100)
sR3 = Slider(axR3, 'R3', 100, 100000, valinit=5000)

def update(val):
    c1 = sC1.val *0.000000000001
    c2 = sC2.val *0.000000000001
    r1 = sR1.val
    r2 = sR2.val
    r3 = sR3.val
    numu = [-1/(c1 * r1), 0]          #bunsi
    denu = [1, 1/(c2 * r3) + 1/(c1 * r3), 1/(r3 * c1* c2)*(1/r1 + 1/r2)]   #bunbo
    Gu   = signal.lti(numu, denu)
    wu, magu, phaseu = signal.bode(Gu,  w = np.arange(1E+6, 1E+10, 1E+4))
    l.set_ydata(magu)
    fig.canvas.draw_idle()

sR1.on_changed(update)
sR2.on_changed(update)
sR3.on_changed(update)
sC1.on_changed(update)
sC2.on_changed(update)

# resetax = plt.axes([0.8, 0.025, 0.1, 0.04])
# button = Button(resetax, 'Reset', color=axcolor, hovercolor='0.975')


# def reset(event):
#     sfreq.reset()
#     samp.reset()
# button.on_clicked(reset)

rax = plt.axes([0.025, 0.5, 0.15, 0.15], facecolor=axcolor)
radio = RadioButtons(rax, ('red', 'blue', 'green'), active=0)


def colorfunc(label):
    l.set_color(label)
    fig.canvas.draw_idle()
radio.on_clicked(colorfunc)

plt.show()