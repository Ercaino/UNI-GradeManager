## Tree Structure (GitHub Action)

1. Create .github/workflows/update_structure.yml 

#### Locally (with Git)
```bash
#  Nella root del progetto:
mkdir -p .github/workflows
touch .github/workflows/update_structure.yml
```
#### Code Yaml

```yaml
name: Update Project Structure
on:
  push:
    branches: [ "master" ]
  workflow_dispatch:  # Permite l'esecuzione manuale
  schedule:
    - cron: '0 0 * * *'  # Esecuzione giornaliera

jobs:
  update-structure:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Install tree
        run: sudo apt-get install -y tree

      - name: Generate structure
        run: |
          tree -I 'build|bin|*~' --dirsfirst -n > STRUCTURE.md

      - name: Commit changes
        uses: stefanzweifel/git-auto-commit-action@v5
        with:
          commit_message: "chore: Update project structure"
          branch: master

```

## verify

1. After the commit, GitHub will automatically execute the Action (visible in "Actions" in the top bar of the repo)

2. Check that the STRUCTURE.md file is created/updated

#### If you don't have admin permissions

Edit the .github/workflows/update_structure.yml file directly by adding:

```yaml
permissions:
  contents: write  # Permette il commit
```

---