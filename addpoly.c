#include <stdio.h>
#include <stdlib.h>

// Node structure to represent terms in a polynomial
struct Node {
    int coefficient;
    int exponent;
    struct Node* next;
};

// Function to create a new node for a term in a polynomial
struct Node* createNode(int coefficient, int exponent) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->coefficient = coefficient;
    newNode->exponent = exponent;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a term into a polynomial (linked list)
void insertTerm(struct Node** poly, int coefficient, int exponent) {
    struct Node* newNode = createNode(coefficient, exponent);

    if (*poly == NULL) {
        *poly = newNode;
        return;
    }

    struct Node* temp = *poly;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
}

// Function to add two polynomials
struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    while (poly1 != NULL || poly2 != NULL) {
        if (poly1 == NULL) {
            insertTerm(&result, poly2->coefficient, poly2->exponent);
            poly2 = poly2->next;
        } else if (poly2 == NULL) {
            insertTerm(&result, poly1->coefficient, poly1->exponent);
            poly1 = poly1->next;
        } else if (poly1->exponent > poly2->exponent) {
            insertTerm(&result, poly1->coefficient, poly1->exponent);
            poly1 = poly1->next;
        } else if (poly1->exponent < poly2->exponent) {
            insertTerm(&result, poly2->coefficient, poly2->exponent);
            poly2 = poly2->next;
        } else {
            insertTerm(&result, poly1->coefficient + poly2->coefficient, poly1->exponent);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }
    return result;
}

// Function to display a polynomial
void displayPolynomial(struct Node* poly) {
    if (poly == NULL) {
        printf("Polynomial is empty.\n");
        return;
    }

    while (poly != NULL) {
        printf("(%dx^%d) ", poly->coefficient, poly->exponent);
        if (poly->next != NULL) {
            printf("+ ");
        }
        poly = poly->next;
    }
    printf("\n");
}

// Function to free memory allocated for polynomial
void freePolynomial(struct Node* poly) {
    struct Node* temp;
    while (poly != NULL) {
        temp = poly;
        poly = poly->next;
        free(temp);
    }
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    struct Node* result = NULL;
    int choice, coefficient, exponent, n;

    while (1) {
        printf("\n1. Enter terms for Polynomial 1\n");
        printf("2. Enter terms for Polynomial 2\n");
        printf("3. Add Polynomials\n");
        printf("4. Display Resultant Polynomial\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter number of terms for Polynomial 1: ");
                scanf("%d", &n);
                printf("Enter coefficients and exponents for Polynomial 1:\n");
                for (int i = 0; i < n; ++i) {
                    printf("Term %d: ", i + 1);
                    scanf("%d %d", &coefficient, &exponent);
                    insertTerm(&poly1, coefficient, exponent);
                }
                break;
            case 2:
                printf("Enter number of terms for Polynomial 2: ");
                scanf("%d", &n);
                printf("Enter coefficients and exponents for Polynomial 2:\n");
                for (int i = 0; i < n; ++i) {
                    printf("Term %d: ", i + 1);
                    scanf("%d %d", &coefficient, &exponent);
                    insertTerm(&poly2, coefficient, exponent);
                }
                break;
            case 3:
                if (poly1 == NULL || poly2 == NULL) {
                    printf("Please enter terms for both polynomials first.\n");
                    break;
                }
                if (result != NULL) {
                    freePolynomial(result);
                }
                result = addPolynomials(poly1, poly2);
                printf("Polynomial 1: ");
                displayPolynomial(poly1);
                printf("Polynomial 2: ");
                displayPolynomial(poly2);
                printf("Resultant Polynomial: ");
                displayPolynomial(result);
                break;
            case 4:
                if (result != NULL) {
                    printf("Resultant Polynomial: ");
                    displayPolynomial(result);
                } else {
                    printf("Resultant Polynomial is empty.\n");
                }
                break;
            case 5:
                freePolynomial(poly1);
                freePolynomial(poly2);
                freePolynomial(result);
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}
 