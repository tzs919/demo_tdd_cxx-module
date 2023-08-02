pipeline {
    agent any

    triggers {
        GenericTrigger(
                genericVariables: [
                        [key: 'event_name', value: '$.event_name', defaultValue: 'push'],
                        [key: 'project_name', value: '$.project.name', defaultValue: 'default'],
                        [key: 'ref', value: '$.ref', defaultValue: 'default'],
                        [key: 'tag', value: '$.ref', defaultValue: 'default', regexpFilter: '.*/'],
                        [key: 'project_id', value: '$.project.id'],    // 项目ID
                        [key: 'project_abbreviation', value: '$.project.name', regexpFilter: '.*-', defaultValue: 'default'],     // 项目简称
                        [key: 'group_name', value: '$.project.namespace'], // GITLAB_GROUP
                        [key: 'commits_id', value: '$.after']// 触发请求中的last_commit.id
                ],
                token: 'demo_tdd_cxx',
                causeString: ' Triggered on $project_name',
                printContributedVariables: true,
                printPostContent: true,
                regexpFilterText: '$commits_id',
                regexpFilterExpression: '[^0]{1,10}'
        )
    }

    stages {
      
        //注意会将检查结果报送到SonarQube，使用的是jenkins里的SonarQube配置，包括访问地址、用户名密码
        stage('Sonar Analysis') {
            when {
                expression { return true; }
            }
            tools {
                jdk 'jdk17'
            }
            steps {
                echo "Sonar Analysis"

               script {
                SCANNER_HOME = tool 'myscanner'
               }
               withSonarQubeEnv('mysonar') {
                   bat "${SCANNER_HOME}/bin/sonar-scanner"
               }
            }
        }

        //等待SonarQube返回的质量阈状态
        stage("Quality Gate") {
            when {
                expression { return true; }
            }
            steps {
                timeout(time: 1, unit: 'HOURS') {
                    //如果不加waitForQualityGate，withSonarQubeEnv也可以获得质量门的状态，但是无法取消流水线
                    //abortPipeline: false，waitForQualityGate有与没有效果一样
                    // Parameter indicates whether to set pipeline to UNSTABLE if Quality Gate fails
                    // true = set pipeline to UNSTABLE, false = don't
                    waitForQualityGate abortPipeline: true
                }
            }
        }

    }

    post {
        always {
            echo '-----build completed-----'
            // deleteDir()
        }
        failure {
            echo '-----build failure-----'
        }
        success {
            echo '-----build success-----'
        }
    }
}
