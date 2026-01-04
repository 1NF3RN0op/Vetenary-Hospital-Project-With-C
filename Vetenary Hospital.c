#include <stdio.h>
#include <string.h>

/*================================= MAIN STRUCTURES ================================= */

struct Doctor
{
    int id;
    char name[50];
    char degree[80];
    float fee;
    char username[30];
    char password[30];
};

struct Owner
{
    int id;
    char name[50];
    char username[30];
    char password[30];
};

struct Appointment
 {
    int appointmentID;
    int doctorID;
    char ownerName[50];
    char petName[30];
    char symptoms[200];
    char status[20];
};

//*================================= FUNCTION DECLARATIONS ================================= *\\

//*----* ADMIN *----*\\

void initializeAdmin();
void mainMenu();

//*----* ADMIN MENU *----*\\

void adminLogin();
void adminMenu();
void addDoctor();
void removeDoctor();
void viewTotalPatients();
void viewRevenue();

//*----* ADMIN *----*\\

void doctorLogin();
void doctorMenu(int doctorID, float fee);
void viewDoctorAppointments(int doctorID);
void writePrescription(int doctorID, float fee);

//*----* PET OWNER *----*\\

void ownerLogin();
void ownerRegister();
void ownerMenu(int ownerID, char ownerName[]);
void bookAppointment(int ownerID, char ownerName[]);
void viewPrescription();

//*----* UTILITY *----*\\

int generateAppointmentID();
float getDoctorFee(int doctorID);
void clearInputBuffer();

//*================================= START OF UTILITIES ================================= *\\

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//*----* INITIALIZE ADMIN *----*\\

void initializeAdmin()
{
    FILE *fp = fopen("admin.txt", "r");
    if (fp)
        {
            fclose(fp);
            return;
        }

    fp = fopen("admin.txt", "w");
    fprintf(fp, "admin admin123");

    fclose(fp);
}

//*================================= INITIALIZE MAIN MENU ================================= *\\

void mainMenu()
{
    int choice;

    while (1)
    {
        printf("\n===== VETERINARY HOSPITAL SYSTEM =====\n");
        printf("1. Admin\n");
        printf("2. Doctor\n");
        printf("3. Pet Owner\n");
        printf("0. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        clearInputBuffer();

        switch (choice)
        {
            case 1: adminLogin();
            break;
            case 2: doctorLogin();
            break;
            case 3: ownerLogin();
            break;
            case 0:
                return;
            default:
                printf("Invalid option!\n");
        }
    }
}

//*================================= START OF ADMIN MENU ================================= *\\

//*----* ADMIN LOGIN *----*\\

void adminLogin()
{
    char u[30], p[30], fu[30], fpw[30];

    FILE *fp = fopen("admin.txt", "r");
    fscanf(fp, "%s %s", fu, fpw);

    fclose(fp);

    printf("Admin Username: ");
    scanf("%s", u);

    printf("Password: ");
    scanf("%s", p);

    clearInputBuffer();

    if (strcmp(u, fu) == 0 && strcmp(p, fpw) == 0)
    {
        adminMenu();
    }

    else
    {
        printf("Wrong admin credentials!\n");
    }
}

//*----* INITIALIZE ADMIN MENU *----*\\

void adminMenu()
{
    int ch;

    while (1)
    {
        printf("\n===== ADMIN PANEL =====\n");
        printf("1. Add Doctor\n");
        printf("2. Remove Doctor\n");
        printf("3. Total Patients Visited\n");
        printf("4. Hospital Revenue\n");
        printf("0. Logout\n");
        printf("Choose: ");
        scanf("%d", &ch);

        clearInputBuffer();

        switch (ch)
        {
            case 1: addDoctor();
            break;
            case 2: removeDoctor();
            break;
            case 3: viewTotalPatients();
            break;
            case 4: viewRevenue();
            break;
            case 0:
                return;
            default:
                 printf("Invalid option!\n");
        }
    }
}


//*----* ADD DOCTORS *----*\\


void addDoctor()
{
    struct Doctor d;
    FILE *fp = fopen("doctors.txt", "a");

    printf("Doctor ID: ");
    scanf("%d", &d.id);

    clearInputBuffer();

    printf("Doctor Name: ");
    fgets(d.name, sizeof(d.name), stdin);
    d.name[strcspn(d.name, "\n")] = 0;

    printf("Degree: ");
    fgets(d.degree, sizeof(d.degree), stdin);
    d.degree[strcspn(d.degree, "\n")] = 0;

    printf("Visiting Fee: ");
    scanf("%f", &d.fee);

    clearInputBuffer();

    printf("Username: ");
    scanf("%s", d.username);

    printf("Password: ");
    scanf("%s", d.password);

    clearInputBuffer();

    fprintf(fp, "%d|%s|%s|%.2f|%s|%s\n",d.id, d.name, d.degree, d.fee,d.username, d.password);

    fclose(fp);

    printf("Doctor added successfully.\n");
}

//*----* REMOVES DOCTORS *----*\\

void removeDoctor()
{
    struct Doctor d;
    int id, found = 0;

    FILE *fp = fopen("doctors.txt", "r");
    FILE *tmp = fopen("temp.txt", "w");

    printf("Enter Doctor ID to remove: ");
    scanf("%d", &id);

    clearInputBuffer();

    while (fscanf(fp, "%d|%49[^|]|%79[^|]|%f|%29[^|]|%29[^\n]\n",&d.id, d.name, d.degree, &d.fee,d.username, d.password) != EOF)
    {
        if (d.id != id)
            fprintf(tmp, "%d|%s|%s|%.2f|%s|%s\n",d.id, d.name, d.degree, d.fee,d.username, d.password);
        else
            found = 1;
    }

    fclose(fp);
    fclose(tmp);

    remove("doctors.txt");
    rename("temp.txt", "doctors.txt");

    if (found) printf("Doctor removed.\n");
    else printf("Doctor not found.\n");
}


//*----* VIEWS TOTAL PATIENTS *----*\\


void viewTotalPatients()
{
    FILE *fp = fopen("appointments.txt", "r");

    int count = 0;
    char line[400];

    if (!fp)
    {
        printf("No patients yet.\n");

        return;
    }

    while (fgets(line, sizeof(line), fp))
    {
        count++;
    }

    fclose(fp);

    printf("Total patients visited: %d\n", count);
}


//*----* VIEWS TOTAL REVENUE *----*\\


void viewRevenue()
{
    FILE *fp = fopen("revenue.txt", "r");
    float sum = 0, x;

    if (!fp)
    {
        printf("No revenue yet.\n");

        return;
    }

    while (fscanf(fp, "%f", &x) != EOF)
    {
        sum += x;
    }

    fclose(fp);

    printf("Total hospital revenue: %.2f\n", sum);
}


//*================================= START OF DOCTOR MENU ================================= *\\


//*----* DOCTOR LOGIN PORTAL *----*\\


void doctorLogin()
{
    struct Doctor d;
    char u[30], p[30];
    int found = 0;

    FILE *fp = fopen("doctors.txt", "r");
    if (!fp)
    {
        printf("No doctors available.\n");

        return;

    }

    printf("Doctor Username: ");
    scanf("%s", u);

    printf("Password: ");
    scanf("%s", p);

    clearInputBuffer();

    while (fscanf(fp, "%d|%49[^|]|%79[^|]|%f|%29[^|]|%29[^\n]\n",&d.id, d.name, d.degree, &d.fee,d.username, d.password) != EOF)
    {
        if (strcmp(u, d.username) == 0 && strcmp(p, d.password) == 0)
        {
            found = 1;
            doctorMenu(d.id, d.fee);

            break;

        }
    }

    fclose(fp);

    if (!found)
    {
        printf("Invalid doctor login!\n");
    }

}



//*----* DOCTOR MENU  *----*\\


void doctorMenu(int doctorID, float fee)
{
    int ch;

    while (1)
    {
        printf("\n===== DOCTOR PANEL =====\n");
        printf("1. View Appointment Queue\n");
        printf("2. Write Prescription\n");
        printf("0. Logout\n");
        printf("Choose: ");
        scanf("%d", &ch);

        clearInputBuffer();

        if (ch == 1) viewDoctorAppointments(doctorID);
        else if (ch == 2) writePrescription(doctorID, fee);
        else if (ch == 0) return;
        else printf("Invalid option!\n");

    }
}


//*----* VIEWS DOCTOR APPOINTMENT *----*\\


void viewDoctorAppointments(int doctorID)
{
    struct Appointment a;
    int found = 0;

    FILE *fp = fopen("appointments.txt", "r");

    if (!fp)
    {
        printf("No appointments.\n");
        return;
    }

    while (fscanf(fp, "%d|%d|%49[^|]|%29[^|]|%199[^|]|%19[^\n]\n",&a.appointmentID, &a.doctorID,a.ownerName, a.petName,a.symptoms, a.status) != EOF)
    {
        if (a.doctorID == doctorID && strcmp(a.status, "Pending") == 0)
        {
            found = 1;
            printf("\nAppointment ID: %d\nOwner: %s\nPet: %s\nSymptoms: %s\n",a.appointmentID, a.ownerName,a.petName, a.symptoms);
        }
    }

    fclose(fp);
    if (!found) printf("No pending appointments.\n");

}


//*----* WRITE PESCRIPTION *----*\\


void writePrescription(int doctorID, float fee)
{
    struct Appointment a;
    int id, found = 0;
    char diagnosis[300];

    FILE *fp = fopen("appointments.txt", "r");
    FILE *tmp = fopen("temp.txt", "w");
    FILE *rp = fopen("reports.txt", "a");

    printf("Enter Appointment ID: ");
    scanf("%d", &id);

    clearInputBuffer();

    while (fscanf(fp, "%d|%d|%49[^|]|%29[^|]|%199[^|]|%19[^\n]\n",&a.appointmentID, &a.doctorID,a.ownerName, a.petName,a.symptoms, a.status) != EOF)
    {
        if (a.appointmentID == id && a.doctorID == doctorID && strcmp(a.status, "Pending") == 0)
        {
            found = 1;

            printf("Write Diagnosis:\n");
            fgets(diagnosis, sizeof(diagnosis), stdin);
            diagnosis[strcspn(diagnosis, "\n")] = 0;

            fprintf(rp,"Appointment %d | Owner: %s | Pet: %s | Diagnosis: %s\n",a.appointmentID, a.ownerName, a.petName, diagnosis);

            strcpy(a.status, "Done");
        }

        fprintf(tmp, "%d|%d|%s|%s|%s|%s\n",a.appointmentID, a.doctorID,a.ownerName, a.petName,a.symptoms, a.status);
    }

    fclose(fp);
    fclose(tmp);
    fclose(rp);

    remove("appointments.txt");
    rename("temp.txt", "appointments.txt");

    if (found)
        printf("Prescription saved successfully.\n");

    else
        printf("Appointment not found.\n");

}


//*================================= START OF PET OWNERS MENU ================================= *\\


//*----* PET OWNER LOGIN *----*\\


void ownerLogin()
{
    int ch;

    printf("\n1. Login\n2. Register\nChoose: ");
    scanf("%d", &ch);

    clearInputBuffer();

    if (ch == 2)
    {
        ownerRegister();

        return;

    }

    struct Owner o;
    char u[30], p[30];
    int found = 0;

    FILE *fp = fopen("owners.txt", "r");

    if (!fp)
    {
        printf("No owners registered.\n");

        return;
    }

    printf("Username: ");
    scanf("%s", u);

    printf("Password: ");
    scanf("%s", p);

    clearInputBuffer();

    while (fscanf(fp, "%d|%49[^|]|%29[^|]|%29[^\n]\n",&o.id, o.name, o.username, o.password) != EOF)
    {
        if (strcmp(u, o.username) == 0 &&
            strcmp(p, o.password) == 0)
        {
            found = 1;
            ownerMenu(o.id, o.name);

            break;
        }
    }

    fclose(fp);

    if (!found) printf("Invalid login!\n");

}


//*----* REGISTRATION OF PET OWNER *----*\\


void ownerRegister()
{
    struct Owner o;
    FILE *fp = fopen("owners.txt", "a");

    printf("Owner ID: ");
    scanf("%d", &o.id);

    clearInputBuffer();

    printf("Owner Name: ");
    fgets(o.name, sizeof(o.name), stdin);
    o.name[strcspn(o.name, "\n")] = 0;

    printf("Username: ");
    scanf("%s", o.username);

    printf("Password: ");
    scanf("%s", o.password);

    clearInputBuffer();

    fprintf(fp, "%d|%s|%s|%s\n",o.id, o.name, o.username, o.password);

    fclose(fp);
    printf("Registration successful.\n");

}


//*----* PET OWNERS MENU *----*\\


void ownerMenu(int ownerID, char ownerName[])
{
    int ch;

    while (1)
    {
        printf("\n===== PET OWNER PANEL =====\n");
        printf("1. Book Appointment\n");
        printf("2. View Prescription\n");
        printf("0. Logout\n");
        printf("Choose: ");
        scanf("%d", &ch);

        clearInputBuffer();

        if (ch == 1) bookAppointment(ownerID, ownerName);

        else if (ch == 2) viewPrescription();

        else if (ch == 0) return;

        else printf("Invalid option!\n");

    }
}


//*----* GENERATES APPOINTMENT ID *----*\\


int generateAppointmentID()
{
    FILE *fp = fopen("appointments.txt", "r");

    int count = 0;
    char line[400];

    if (!fp) return 1;

    while (fgets(line, sizeof(line), fp)) count++;
    fclose(fp);

    return count + 1;

}


//*----* GETS DOCTORS FEE *----*\\


float getDoctorFee(int doctorID)
{

    struct Doctor d;
    FILE *fp = fopen("doctors.txt", "r");


    while (fscanf(fp, "%d|%49[^|]|%79[^|]|%f|%29[^|]|%29[^\n]\n",&d.id, d.name, d.degree, &d.fee,d.username, d.password) != EOF)
    {
        if (d.id == doctorID)

        {
            fclose(fp);
            return d.fee;
        }
    }

    fclose(fp);

    return 0;
}


//*----* BOOKS APPOINMENT *----*\\


void bookAppointment(int ownerID, char ownerName[])
{
    struct Appointment a;

    FILE *fp = fopen("appointments.txt", "a");
    FILE *rev = fopen("revenue.txt", "a");


    a.appointmentID = generateAppointmentID();


    printf("Doctor ID: ");
    scanf("%d", &a.doctorID);
    clearInputBuffer();


    printf("Pet Name: ");
    fgets(a.petName, sizeof(a.petName), stdin);
    a.petName[strcspn(a.petName, "\n")] = 0;


    printf("Symptoms:\n");
    fgets(a.symptoms, sizeof(a.symptoms), stdin);
    a.symptoms[strcspn(a.symptoms, "\n")] = 0;


    strcpy(a.ownerName, ownerName);
    strcpy(a.status, "Pending");


    fprintf(fp, "%d|%d|%s|%s|%s|%s\n",
            a.appointmentID, a.doctorID,
            a.ownerName, a.petName,
            a.symptoms, a.status);


    float fee = getDoctorFee(a.doctorID);
    fprintf(rev, "%.2f\n", fee);


    fclose(fp);
    fclose(rev);


    printf("Appointment booked successfully!\n");
    printf("Visiting fee %.2f paid.\n", fee);

}


//*----* VIEW PESCRIPTION *----*\\


void viewPrescription()
{

    FILE *fp = fopen("reports.txt", "r");
    char line[500];

    if (!fp)
        {
            printf("No prescriptions yet.\n");
            return;
        }

    printf("\n--- PRESCRIPTIONS ---\n");

    while (fgets(line, sizeof(line), fp))

        printf("%s", line);

    fclose(fp);
}


//*================================= MAIN MENU ================================= *\\


int main()
{

    initializeAdmin();
    mainMenu();

    return 0;

}
