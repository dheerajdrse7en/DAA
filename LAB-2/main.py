import random
import names
import csv
import os

# Job roles expanded with some prefixes for variety
job_roles = [
    "HRM", "HRBP", "HRGA", "HRD",
    "CFO", "FP&A", "ACC", "AP/AR", "FA",
    "CMO", "PM", "SMM", "SEO", "PPC",
    "VP of Sales", "AE", "SDR", "BDM",
    "CIO", "Dev", "QA", "SysAdmin", "DBA",
    "ITSM", "DevOps", "CTO", "PMO", "Network Admin",
    "Security Analyst", "UX/UI", "Data Scientist",
    "Data Analyst", "Cloud Engineer",
    "GC", "AGC", "IP", "Corp Counsel",
    "COO", "Ops Manager", "Procurement Manager",
    "Supply Chain Analyst", "CSM", "CSR",
    "Support Engineer", "Help Desk",
    "CPO", "PM", "UX Designer", "Product Analyst"
]

DATASET_DIR = "dataset"
os.makedirs(DATASET_DIR, exist_ok=True)  # Ensure directory exists

def generate_name():
    """Generate a random full name."""
    return names.get_full_name()

def best_scenario(size):
    with open(f"{DATASET_DIR}/ascending_employees_{size}.csv", "w", newline='') as f:
        writer = csv.writer(f)
        writer.writerow(["EmployeeID", "Name", "Department", "Salary"])
        for num in range(1, size + 1):
            writer.writerow([
                num,
                generate_name(),
                random.choice(job_roles),
                random.randint(12000, 160000)  # Slightly broader range
            ])

def worst_scenario(size):
    with open(f"{DATASET_DIR}/descending_employees_{size}.csv", "w", newline='') as f:
        writer = csv.writer(f)
        writer.writerow(["EmployeeID", "Name", "Department", "Salary"])
        for num in range(size, 0, -1):
            writer.writerow([
                num,
                generate_name(),
                random.choice(job_roles),
                random.randint(10000, 150000)
            ])

def average_scenario(size):
    idx = list(range(1, size + 1))
    random.shuffle(idx)
    with open(f"{DATASET_DIR}/random_employees_{size}.csv", "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["EmployeeID", "Name", "Department", "Salary"])
        for i in idx:
            writer.writerow([
                i,
                generate_name(),
                random.choice(job_roles),
                random.randint(15000, 155000)
            ])

def main():
    for size in [5000, 10000, 20000]:
        best_scenario(size)
        worst_scenario(size)
        average_scenario(size)

if __name__ == "__main__":
    main()
