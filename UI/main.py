#!/usr/bin/env python3
"""
TrailBlazer - Operator GUI (MVP)
=================================

Standalone Tkinter prototype covering the two GUI phases described in the
41068 C1 proposal:

  Phase 1 - Teleop Mapping
      The ranger drives the simulated rover with W / A / S / D to trace out
      the hiking trail network. Waypoint and junction nodes are recorded as
      the rover moves.

  Phase 2 - Autonomous Inspection
      The recorded nodes are joined, in the order they were created, by
      black route lines. The operator can seed simulated storm obstacles,
      then run the autonomous inspection: each route turns green once the
      rover clears it, or red if an obstacle blocks it (with the rover
      backtracking to the previous junction).

This GUI is self-contained (pure Tkinter, no extra dependencies) so it can
be run and iterated on immediately. The rover motion in Phase 1 and the
obstacle check in Phase 2 are lightweight simulations, deliberately kept in
their own small methods (`Phase1Frame._move_robot`,
`Phase2Frame._arrive_at_edge_end`) so they're easy to swap out for the real
SLAM / Nav2 / perception topics as those work streams come online.

Live camera:
      Both tabs show a live camera panel fed from the simulation topic
      /husky1/camera/image (override with the TRAILBLAZER_CAMERA_TOPIC
      environment variable). Source ROS 2 (and your workspace) in the terminal
      first; without it the GUI still runs and the panel explains why it has
      no signal.

Run with:
    python3 main.py
"""
import os
import tkinter as tk
from tkinter import ttk

from camera_feed import CameraFeed, DEFAULT_TOPIC
from state import TrailState
from phase1_teleop import Phase1Frame
from phase2_inspection import Phase2Frame


class TrailBlazerApp:
    def __init__(self, root):
        self.root = root
        self.root.title("TrailBlazer - Operator GUI")
        # The map canvas is a 760x760 square (representing the 15 m x 15 m
        # trail area), so the window needs real height to fit it alongside
        # the title, subtitle and button rows. Resizable with a safe minimum
        # in case a smaller screen can't fit the default size.
        self.root.geometry("1140x1020")
        self.root.minsize(1100, 860)
        self.root.resizable(True, True)

        # 'clam' renders consistently across Linux desktop themes; the default
        # theme on some systems draws ttk widgets (including button labels) as
        # blank flat bars.
        style = ttk.Style(root)
        style.theme_use("clam")

        self.state = TrailState()

        # One ROS camera subscriber shared by both tabs.
        self.camera_feed = CameraFeed(os.environ.get("TRAILBLAZER_CAMERA_TOPIC", DEFAULT_TOPIC))
        self.camera_feed.start()
        self.root.protocol("WM_DELETE_WINDOW", self.on_close)

        self.notebook = ttk.Notebook(root)
        self.notebook.pack(fill="both", expand=True)

        self.phase1 = Phase1Frame(self.notebook, self.state, on_finish_mapping=self._go_to_phase2,
                                 camera_feed=self.camera_feed)
        self.phase2 = Phase2Frame(self.notebook, self.state, camera_feed=self.camera_feed)

        self.notebook.add(self.phase1, text="Phase 1 - Teleop Mapping")
        self.notebook.add(self.phase2, text="Phase 2 - Autonomous Inspection")

        self.notebook.bind("<<NotebookTabChanged>>", self._on_tab_changed)

    def on_close(self):
        self.camera_feed.stop()          # shuts the ROS subscriber down cleanly
        self.root.destroy()

    def _go_to_phase2(self):
        self.phase2.refresh_from_state()
        self.notebook.select(self.phase2)

    def _on_tab_changed(self, _event):
        if self.notebook.index(self.notebook.select()) == 0:
            self.phase1.focus_canvas()


if __name__ == "__main__":
    root = tk.Tk()
    app = TrailBlazerApp(root)
    root.mainloop()