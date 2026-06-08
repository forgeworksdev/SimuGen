unsigned long long factorial(int n) {
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

/* 
  A Gene is a sequence of DNA that defines the production of any given compount
  made to espress a characteristic
*/
struct Gene {
  char name = 'A';
  bool dominant = true;
  
  Gene() {}

  Gene(char name, bool dominant): name(name), dominant(dominant) {}
};

/* 
  A Genotype is the conjuction of two genes (two alleles), one from the mother
  and one from the father. They are responsible for expressing the Fenotype (characteristic).
*/
class Genotype {
  public:
    std::vector<Gene> alleles;

    Genotype() {}

    Genotype(Gene allele1, Gene allele2) {
      alleles.push_back(allele1);
      alleles.push_back(allele2);
    }

    Genotype(Gene allele1) {
      alleles.push_back(allele1);
    }
};

/* 
  A Parent is any given living being. He contains a series of Genotypes (characteristics), which each contain two genes.
*/
struct Parent {
  public:
    std::vector<Genotype> genotypes;

    String name = "John Cena";
    

    Parent() {}

    Parent(String name): name(name) {}
};

std::vector<Genotype> getGametes(Parent parent) {
  std::vector<Genotype> result;

  for (Genotype& g : parent.genotypes) {
      if (g.alleles[0].name == g.alleles[1].name) {
          // Homozigoto
          result.push_back(Genotype(g.alleles[0]));
      } else {
          // Heterozigoto
          result.push_back(Genotype(g.alleles[0]));
          result.push_back(Genotype(g.alleles[1]));
      }
  }
return result;
}


std::vector<Genotype> getChildPossibleGenotypes(Parent parent1, Parent parent2) {
  std::vector<Genotype> result;

  std::vector<Genotype> parent1Gametes = getGametes(parent1);
  std::vector<Genotype> parent2Gametes = getGametes(parent2);
  
  for (Genotype& g1 : parent1Gametes) {
      for (Genotype& g2 : parent2Gametes) {

          Gene one = g1.alleles[0];
          Gene two = g2.alleles[0];

          result.push_back(Genotype(one, two));
      }
  }
  return result;
}


void prog() {
  M5.Log(ESP_LOG_WARN    , "SimuGen Indev");
  M5.Log.printf("By ForgeWorks");
  M5.Log.printf("\n");
  M5.Log.printf("\n");

  Parent parent1("Parent1");
  Parent parent2("Parent2");

  Gene a('a', false);
  Gene A('A', true);

  Genotype geno1(A, A);
  Genotype geno2(A, a);
  parent1.genotypes.push_back(geno1);
  parent2.genotypes.push_back(geno2);


  M5.Log.printf("Nome do pai 1:\n");
  M5.Log.printf("%s\n", parent1.name.c_str());
  M5.Log.printf("\tGenotipos do pai 1: ");
  for (Genotype& g: parent1.genotypes) {
    for (Gene& k: g.alleles) {
      M5.Log.printf("%c", k.name);
    }
    M5.Log.printf("\n");
  }
  M5.Log.printf("\n");
  M5.Log.printf("Nome do pai 2:\n");
  M5.Log.printf("%s\n", parent2.name.c_str());
  M5.Log.printf("\tGenotipos do pai 2: ");
  for (Genotype& g: parent2.genotypes) {
    for (Gene& k: g.alleles) {
      M5.Log.printf("%c", k.name);
    }
    M5.Log.printf("\n");
  }

  M5.Log.printf("\n");
  M5.Log.printf("\n");


  M5.Log.printf("\tGenotipos possíveis do filho: \n");
  std::vector<Genotype> b = getChildPossibleGenotypes(parent1, parent2);

  for (Genotype& g: b) {
    for (Gene& k: g.alleles) {
      M5.Log.printf("%c", k.name);
    }
    M5.Log.printf("\n");
  }

  //uint8_t k = 2;

  //auto num = factorial(n) / (factorial(k) * factorial(n - k));
  //M5.Log.printf("%d\n", num);
}


double calculateProbability(int favorable, int total) {
  if (total == 0) return 0.0;
  return static_cast<double>(favorable) / total;
}

// Recursive backtracking combination.
// https://www.sanfoundry.com/cpp-program-possible-combinations-list-numbers
template <typename T>
void combine(T a[], int collectionSize, int start, int currIteration, bool check[], int len) {
	if(currIteration > collectionSize) {
	    return;
	} else if (currIteration == collectionSize) {
		//cout<<"\t";
		for (int i = 0; i < len; i++) {
			if (check[i] == true) {
				//cout<<a[i]<<" ";
			}
		}
		//cout<<"\n";
		return;
	}
	
	if (start == len) return;

	check[start] = true;
	combine(a, collectionSize, start + 1, currIteration + 1, check, len);

	check[start] = false;
	combine(a, collectionSize, start + 1, currIteration, check, len);
}

