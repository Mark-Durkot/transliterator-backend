pipeline{

        agent { label 'transliterator-backend-agent' }

        environment {
                DOCKERHUB_CREDENTIALS=credentials('dockerhub-markdurkot')
        }

        stages {

                stage('Build') {

                        steps {
                                sh 'docker build -t markdurkot/transliterator-backend:latest .'
                        }
                }

                stage('Login') {

                        steps {
                                sh 'echo $DOCKERHUB_CREDENTIALS_PSW | docker login -u $DOCKERHUB_CREDENTIALS_USR --password-stdin'
                        }
                }

                stage('Push') {

                        steps {
                                sh 'docker push markdurkot/transliterator-backend:latest'
:latest'
                        }
                }
        }

        post {
                always {
                        sh 'docker logout'
                }
        }

}
