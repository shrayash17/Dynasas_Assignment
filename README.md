# Dynasas_Assignment :  This README file that provides an overview of the project, descriptions of the files.

waveform_generator.cpp

Description: C++ source code that generates waveform data based on user-defined parameters such as waveform type, frequency, amplitude, phase shift, duration, and sample rate.
Functionality: Prompts the user for input parameters, generates the waveform data, and saves the data to waveform_data.csv.


waveform_data.csv

Description: CSV file that stores the generated waveform data.
Structure:
Columns:
Time: Time in seconds.
Amplitude: Amplitude of the waveform at the corresponding time.
Usage: Serves as the input data for visualization scripts.


plot_matplotlib.py

Description: Python script that visualizes the waveform data using the Matplotlib library.
Functionality: Reads waveform_data.csv, optionally downsamples the data for performance, and plots the waveform as a static graph.
plot_datashader.py

Description: Python script that visualizes the waveform data using the Datashader library.
Functionality: Efficiently renders large datasets by rasterizing the waveform data into an image, providing a clear visualization even with a high number of data points.
plot_plotly.py

Description: Python script that visualizes the waveform data using the Plotly library.
Functionality: Creates an interactive plot of the waveform, allowing users to zoom, pan, and hover over data points for detailed inspection.
