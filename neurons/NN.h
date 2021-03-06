#pragma once
#include "Matrix.h"
#include "Functions.h"
#include "NN_layer.h"
#include "Dataset.h"
#include <iostream>
#include <random>

class NN
{
private:
    std::default_random_engine m_train_rand;
    std::default_random_engine m_test_rand;
    std::uniform_int_distribution<size_t> m_train_distribution;
    std::uniform_int_distribution<size_t> m_test_distribution;

protected:
    // The learning rate
    double m_l_rate;

    lint m_batch_size;

    lint m_threads;
    // Steps of the training
    lint m_steps;

    lint m_epoch_size;
    // Training time allowed
    lint m_secs_allowed;

    // The training set
    std::vector<neurons::Matrix> m_train_set;
    // The training label
    std::vector<neurons::Matrix> m_train_labels;
    // The test set
    std::vector<neurons::Matrix> m_test_set;
    // The test label
    std::vector<neurons::Matrix> m_test_labels;

    // The layers of neural network
    std::vector<std::shared_ptr<neurons::NN_layer>> m_layers;

public:
    NN(
        double l_rate,
        lint batch_size,
        lint threads,
        lint steps,
        lint epoch_size,
        lint secs_allowed,
        const dataset::Dataset &d_set);

    ~NN();

    NN(const NN & other) = delete;
    NN(NN && other) = delete;
    NN & operator = (const NN & other) = delete;
    NN & operator = (NN && other) = delete;

public:

    virtual void print_layers(std::ostream & os) const = 0;

    void print_train_set(std::ostream & os) const;

    void print_train_label(std::ostream & os) const;

    void print_test_set(std::ostream & os) const;

    void print_test_label(std::ostream & os) const;

public:
    void train();

    void test();

private:

    void get_batch(
        std::vector<std::vector<neurons::Matrix>> & data_batch,
        std::vector<std::vector<neurons::Matrix>> & label_batch,
        const std::vector<neurons::Matrix> & data,
        const std::vector<neurons::Matrix> & label,
        std::default_random_engine & rand_generator,
        std::uniform_int_distribution<size_t> & distribution);


    double train_step(
        const std::vector<std::vector<neurons::Matrix>> & inputs,
        const std::vector<std::vector<neurons::Matrix>> & targets,
        std::vector<std::vector<neurons::Matrix>> & preds);

    double test_step(
        const std::vector<std::vector<neurons::Matrix>> & inputs,
        const std::vector<std::vector<neurons::Matrix>> & targets,
        std::vector<std::vector<neurons::Matrix>> & preds);

    double get_accuracy(const neurons::Matrix & pred, const neurons::Matrix & target);

    double get_accuracy(
        const std::vector<std::vector<neurons::Matrix>> & preds,
        const std::vector<std::vector<neurons::Matrix>> & targets);

    virtual std::vector<neurons::Matrix> test(
        const std::vector<neurons::Matrix> & inputs,
        const std::vector<neurons::Matrix> & targets,
        lint thread_id) = 0;

    virtual std::vector<neurons::Matrix> optimise(
        const std::vector<neurons::Matrix> & inputs,
        const std::vector<neurons::Matrix> & targets,
        lint thread_id) = 0;
};

std::ostream & operator << (std::ostream & os, const NN & nn);


