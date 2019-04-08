pipeline {
  agent {
    docker {
      image 'epitechcontent/epitest-docker'
    }

  }
  stages {
    stage('Make') {
      steps {
        sh 'make'
      }
    }
    stage('Test') {
      parallel {
        stage('Unit test') {
          steps {
            sh 'make tests_run'
          }
        }
        stage('Functional test') {
          steps {
            sh 'chmod +x ./ci/tests/*'
            sh './ci/tests/tester.sh'
          }
        }
      }
    }
    stage('Clean up') {
      steps {
        sh 'make fclean'
      }
    }
  }
}