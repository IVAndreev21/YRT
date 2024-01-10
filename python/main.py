import tkinter as tk
from tkinter import ttk, messagebox

class RoundedDialog(tk.Toplevel):
    def __init__(self, parent, title, message):
        super().__init__(parent)
        self.title(title)
        self.configure(bg="#00796b")

        self.label = ttk.Label(self, text=message, foreground="white", background="#00796b", font=("Helvetica", 12))
        self.label.pack(padx=20, pady=10)

        self.ok_button = ttk.Button(self, text="OK", command=self.destroy, style="Rounded.TButton")
        self.ok_button.pack(pady=10)

        self.style = ttk.Style()
        self.style.configure("Rounded.TButton", background="#00796b", foreground="white", padding=(10, 5))
        self.rounded_corners()

    def rounded_corners(self):
        self.overrideredirect(1)
        self.attributes('-topmost', True)
        self.geometry('+%d+%d' % (self.winfo_screenwidth() / 2 - 150, self.winfo_screenheight() / 2 - 75))
        self.update_idletasks()
        self.config(width=self.winfo_width(), height=self.winfo_height())
        self.geometry('%dx%d' % (self.winfo_width() + 10, self.winfo_height() + 10))

def generate_digital_will():
    name = name_entry.get()
    assets = assets_text.get("1.0", "end-1c")
    beneficiaries = beneficiaries_text.get("1.0", "end-1c")

    digital_will = f"Digital Will\n\nName: {name}\n\nAssets:\n{assets}\n\nBeneficiaries:\n{beneficiaries}"

    dialog = RoundedDialog(root, "Digital Will", digital_will)

def create_label_entry_pair(frame, label_text, row):
    label = ttk.Label(frame, text=label_text, font=("Helvetica", 12, "bold"), foreground="#2e2e2e")
    label.grid(row=row, column=0, sticky=tk.W, pady=(10, 5))

    entry = ttk.Entry(frame, font=("Helvetica", 12), justify="left")
    entry.grid(row=row, column=1, sticky=tk.W, pady=(10, 5))

    return entry

def create_label_text_pair(frame, label_text, row):
    label = ttk.Label(frame, text=label_text, font=("Helvetica", 12, "bold"), foreground="#2e2e2e")
    label.grid(row=row, column=0, sticky=tk.W, pady=(10, 5))

    text_widget = tk.Text(frame, height=5, width=30, font=("Helvetica", 12), wrap="word")
    text_widget.grid(row=row, column=1, sticky=tk.W, pady=(10, 5))

    return text_widget

root = tk.Tk()
root.title("Digital Will Generator")

style = ttk.Style()
style.configure("TFrame", background="#e0f2f1")
style.configure("TButton", background="#00796b", foreground="black", padding=(10, 5))
style.configure("TLabel", background="#e0f2f1", foreground="#2e2e2e", font=("Helvetica", 16))
style.configure("TEntry", fieldbackground="#f5f5f5")

main_frame = ttk.Frame(root, padding="20")
main_frame.grid(row=0, column=0, sticky=[tk.W, tk.E, tk.N, tk.S])

name_entry = create_label_entry_pair(main_frame, "Name:", 0)
assets_text = create_label_text_pair(main_frame, "Assets:", 1)
beneficiaries_text = create_label_text_pair(main_frame, "Beneficiaries:", 2)

generate_button = ttk.Button(main_frame, text="Generate Digital Will", command=generate_digital_will)
generate_button.grid(row=3, column=0, columnspan=2, pady=20)

root.mainloop()
