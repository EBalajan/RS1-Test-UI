"""
Camera panel widget: shows the newest frame from a CameraFeed, letterboxed
into a fixed-size box, with a status line underneath (LIVE / waiting / no
signal). Used on both the Phase 1 and Phase 2 tabs; they share one feed.
"""
import tkinter as tk
from tkinter import ttk

from PIL import Image, ImageDraw, ImageFont, ImageOps, ImageTk

UPDATE_MS = 100                     # GUI poll rate; the sim camera is only ~3 Hz
BOX_COLOR = (17, 17, 17)
STATUS_COLORS = {
    "live": "#2e7d32",
    "waiting": "#b26a00",
    "stale": "#b26a00",
    "error": "#c0392b",
    "unavailable": "#c0392b",
}


def _make_placeholder(width, height, text="NO SIGNAL"):
    image = Image.new("RGB", (width, height), BOX_COLOR)
    draw = ImageDraw.Draw(image)
    try:
        font = ImageFont.load_default(size=22)
    except TypeError:               # older Pillow can't size the default font
        font = ImageFont.load_default()
    left, top, right, bottom = draw.textbbox((0, 0), text, font=font)
    draw.text(((width - (right - left)) / 2 - left, (height - (bottom - top)) / 2 - top),
              text, fill=(150, 150, 150), font=font)
    return image


class CameraPanel(ttk.Frame):
    def __init__(self, parent, feed, width=300, height=200, title="Live Camera"):
        super().__init__(parent)
        self.feed = feed
        self.box_w = width
        self.box_h = height
        self._shown_id = None
        self._after_id = None

        ttk.Label(self, text=title, font=("Arial", 11, "bold")).pack(anchor="w")

        self._placeholder = ImageTk.PhotoImage(_make_placeholder(width, height))
        self._photo = self._placeholder
        self.image_label = tk.Label(self, image=self._placeholder, bg="#111111",
                                    bd=1, relief="sunken")
        self.image_label.pack(anchor="w", pady=(2, 2))

        self.status_label = ttk.Label(self, text="", wraplength=width, justify="left")
        self.status_label.pack(anchor="w")

        self._refresh()

    def _fit_to_box(self, frame):
        fitted = ImageOps.contain(frame, (self.box_w, self.box_h))
        box = Image.new("RGB", (self.box_w, self.box_h), BOX_COLOR)
        box.paste(fitted, ((self.box_w - fitted.width) // 2, (self.box_h - fitted.height) // 2))
        return box

    def _refresh(self):
        # Skip the work while this tab isn't visible; the frame id check below
        # makes sure we catch up the moment it is shown again.
        if self.winfo_ismapped():
            state, text = self.feed.status()
            self.status_label.configure(text=("\u25cf " if state == "live" else "\u25cb ") + text,
                                        foreground=STATUS_COLORS.get(state, "black"))
            frame_id, frame = self.feed.get_frame()
            if frame is not None and frame_id != self._shown_id:
                self._photo = ImageTk.PhotoImage(self._fit_to_box(frame))
                self.image_label.configure(image=self._photo)
                self._shown_id = frame_id
        self._after_id = self.after(UPDATE_MS, self._refresh)

    def destroy(self):
        if self._after_id is not None:
            self.after_cancel(self._after_id)
            self._after_id = None
        super().destroy()